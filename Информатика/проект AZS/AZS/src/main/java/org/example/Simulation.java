package org.example;

import java.util.*;

public class Simulation {
    // Поля
    private final Config config;
    private final GasStation gasStation;
    private final CarGenerator carGenerator;
    private final EventQueue eventQueue;
    private final Statistics statistics;
    private double currentTime;
    private final double endTime;
    private boolean isRunning;
    private final Random random;

    // Конструктор
    public Simulation(Config config) {
        this.config = config;
        this.random = new Random(config.getRandomSeed());
        this.gasStation = new GasStation(config);
        this.carGenerator = new CarGenerator(random);
        this.eventQueue = new EventQueue();
        this.statistics = new Statistics();
        this.currentTime = 0.0;
        this.endTime = config.getSimulationDays() * 24 * 60;
        this.isRunning = false;
        initialize();
    }

    /**
     * Инициализация всех компонентов
     */
    public void initialize() {
        System.out.println("Инициализация симуляции...");
        scheduleInitialEvents();
        System.out.println("Инициализация завершена. Время симуляции: " +
                formatTime(endTime) + " (" + config.getSimulationDays() + " дней)");
    }

     //Планирование начальных событий
    public void scheduleInitialEvents() {
        // Планируем первое прибытие автомобиля
        double firstArrivalTime = carGenerator.generateNextArrivalTime(0.0);
        eventQueue.add(new Event(Event.Type.ARRIVAL, firstArrivalTime));
        // Планируем первую доставку топлива
        double deliveryTime = config.getDeliveryIntervalHours() * 60;
        eventQueue.add(new Event(Event.Type.FUEL_DELIVERY, deliveryTime));

        System.out.println("Запланированы начальные события:");
        System.out.println("  - Первое прибытие: " + formatTime(firstArrivalTime));
        System.out.println("  - Первая доставка: " + formatTime(deliveryTime));
    }

    //Запуск симуляции
    public void run() {
        isRunning = true;
        System.out.println("\n ЗАПУСК СИМУЛЯЦИИ");
        System.out.println("========================================\n");
        int eventCount = 0;
        int lastProgressPercent = 0;

        while (isRunning && !isSimulationEnded() && !eventQueue.isEmpty()) {
            // Получаем следующее событие
            Event event = eventQueue.poll();
            if (event == null) break;
            currentTime = event.getTime();
            // Выводим прогресс каждые 10%
            int progressPercent = (int)((currentTime / endTime) * 100);
            if (progressPercent >= lastProgressPercent + 10) {
                printProgress();
                lastProgressPercent = progressPercent - (progressPercent % 10);
            }
            // Обрабатываем событие
            processEvent(event);
            eventCount++;

            // Проверяем, не превысили ли время
            if (currentTime > endTime) {
                isRunning = false;
            }
        }

        // Симуляция завершена
        System.out.println("\n\n СИМУЛЯЦИЯ ЗАВЕРШЕНА");
        System.out.println("Обработано событий: " + eventCount);
        System.out.println("Итоговое время: " + formatTime(currentTime));

        // Устанавливаем итоговое количество колонок и время для статистики
        statistics.setFinalPumpsCount(gasStation.getTotalPumpsCount());
        statistics.setTotalSimulationTime(currentTime);
    }

    //Обработка события
    public void processEvent(Event event) {
        switch (event.getType()) {
            case ARRIVAL:
                handleArrival(event);
                break;
            case SERVICE_END:
                handleServiceEnd(event);
                break;
            case FUEL_DELIVERY:
                handleFuelDelivery(event);
                break;
            case PUMP_OPEN:
                handlePumpOpen(event);
                break;
            default:
                System.err.println("Неизвестный тип события: " + event.getType());
        }
    }

    //Обработка прибытия автомобиля
    public void handleArrival(Event event) {
        // Генерируем автомобиль
        Car car = carGenerator.generateCar(currentTime);
        // Записываем в статистику
        statistics.recordArrival();
        // Проверяем, достаточно ли топлива
        if (!gasStation.hasEnoughFuel(car.getDesiredFuel())) {
            statistics.recordRefusal();
        } else {
            // Пытаемся заправить
            boolean started = gasStation.tryRefuelCar(car, currentTime);
            if (started) {
                // Автомобиль начал заправку - планируем событие окончания
                FuelPump pump = gasStation.getPumpForCar(car);
                double endServiceTime = car.getStartServiceTime() +
                        (car.getDesiredFuel() / pump.getFlowRate());

                statistics.recordPumpStart(pump.getId(), currentTime);
                eventQueue.add(new Event(Event.Type.SERVICE_END, endServiceTime, car, pump));
                statistics.recordFuelLevel(gasStation.getFuelReserve(), currentTime);
            } else {
                gasStation.addToQueue(car);
            }
        }

        // Планируем следующее прибытие
        double nextArrivalTime = currentTime +
                carGenerator.generateNextArrivalTime(currentTime);

        if (nextArrivalTime <= endTime) {
            eventQueue.add(new Event(Event.Type.ARRIVAL, nextArrivalTime));
        }
        // Обновляем статистику по очереди
        statistics.recordQueueLength(gasStation.getQueueSize(), currentTime);
    }

    //Обработка окончания заправки
    public void handleServiceEnd(Event event) {
        Car car = event.getCar();
        FuelPump pump = event.getPump();
        double endTime = pump.finishService(currentTime);
        statistics.recordPumpEnd(pump.getId(), currentTime);
        statistics.recordService(car);
        // Проверяем время ожидания для возможного расширения
        double waitTime = car.calculateWaitTime();
        if (waitTime > config.getQueueThresholdMinutes()) {
            // Планируем открытие новой колонки через 2 дня
            double openTime = currentTime + (config.getExpansionDelayDays() * 24 * 60);
            if (openTime <= this.endTime && gasStation.getTotalPumpsCount() < config.getMaxPumps()) {
                eventQueue.add(new Event(Event.Type.PUMP_OPEN, openTime));
            }
        }

        // Если есть очередь, берём следующий автомобиль
        if (!gasStation.isQueueEmpty()) {
            Car nextCar = gasStation.pollFromQueue();

            // Проверяем, достаточно ли топлива
            if (gasStation.hasEnoughFuel(nextCar.getDesiredFuel())) {
                gasStation.startService(nextCar, pump, currentTime);
                statistics.recordPumpStart(pump.getId(), currentTime);
                statistics.recordFuelLevel(gasStation.getFuelReserve(), currentTime);
                double nextEndTime = currentTime + (nextCar.getDesiredFuel() / pump.getFlowRate());
                eventQueue.add(new Event(Event.Type.SERVICE_END, nextEndTime, nextCar, pump));
            } else {
                // Не хватает топлива - отказ
                statistics.recordRefusal();
            }
        }

        // Обновляем статистику по очереди
        statistics.recordQueueLength(gasStation.getQueueSize(), currentTime);
    }

    //Обработка доставки топлива
    public void handleFuelDelivery(Event event) {
        gasStation.processDelivery(currentTime);
        statistics.recordDelivery();
        // Планируем следующую доставку
        double nextDeliveryTime = currentTime +
                (config.getDeliveryIntervalHours() * 60) +
                config.getDeliveryDurationMinutes();

        if (nextDeliveryTime <= endTime) {
            eventQueue.add(new Event(Event.Type.FUEL_DELIVERY, nextDeliveryTime));
        }
        // Записываем уровень топлива
        statistics.recordFuelLevel(gasStation.getFuelReserve(), currentTime);
    }

    //Обработка открытия новой колонки
    public void handlePumpOpen(Event event) {
        // Проверяем, не превышен ли лимит
        if (gasStation.getTotalPumpsCount() >= config.getMaxPumps()) {
            return; // не открываем
        }
        // Открываем новую колонку
        FuelPump newPump = gasStation.openNewPump(config.getDefaultFlowRate(), currentTime, getCurrentDay());
        statistics.recordExpansion();
        // Проверяем, есть ли очередь
        if (!gasStation.isQueueEmpty() && gasStation.hasFreePump()) {
            Car nextCar = gasStation.pollFromQueue();
            FuelPump freePump = gasStation.findFreePump();

            if (gasStation.hasEnoughFuel(nextCar.getDesiredFuel())) {
                gasStation.startService(nextCar, freePump, currentTime);
                statistics.recordPumpStart(freePump.getId(), currentTime);
                double nextEndTime = currentTime +
                        (nextCar.getDesiredFuel() / freePump.getFlowRate());

                eventQueue.add(new Event(Event.Type.SERVICE_END, nextEndTime, nextCar, freePump));
            }
        }
    }
     //Остановка симуляции
    public void stop() {
        isRunning = false;
        System.out.println("\n Симуляция остановлена на времени: " + formatTime(currentTime));
    }

     //Проверка окончания симуляции
    public boolean isSimulationEnded() {
        return currentTime >= endTime;
    }

     //Получить текущий день
    public int getCurrentDay() {
        return (int)(currentTime / (24 * 60)) + 1;
    }

     //Вывод прогресса
    public void printProgress() {
        int percent = (int)((currentTime / endTime) * 100);
        int days = getCurrentDay();

        System.out.printf("\r Прогресс: %d%% | День %d/%d | Время: %s | Очередь: %d | Обслужено: %d",
                percent,
                days,
                config.getSimulationDays(),
                formatTime(currentTime),
                gasStation.getQueueSize(),
                statistics.getTotalServed()
        );
    }
    //Форматирование времени (минуты -> ЧЧ:ММ)
    private String formatTime(double minutes) {
        int totalMinutes = (int) minutes;
        int hours = totalMinutes / 60;
        int mins = totalMinutes % 60;
        int days = hours / 24;
        hours = hours % 24;
        if (days > 0) {
            return String.format("%dд %02d:%02d", days, hours, mins);
        } else {
            return String.format("%02d:%02d", hours, mins);
        }
    }
    //Получить статистику
    public Statistics getStatistics() {
        return statistics;
    }
}