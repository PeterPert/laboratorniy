package org.example;

import java.util.*;

public class Statistics {
    // Счетчики
    private int totalArrivals;          // Всего прибыло автомобилей
    private int totalServed;             // Обслужено автомобилей
    private int totalRefusals;           // Отказано (нехватка топлива)
    // Временные характеристики
    private List<Double> waitTimes;      // Времена ожидания для расчета среднего
    private double maxWaitTime;           // Максимальное время ожидания
    private List<Double> serviceTimes;    // Времена обслуживания
    // Очередь
    private int maxQueueLength;            // Максимальная длина очереди
    private List<Integer> queueLengths;    // Для статистики (если понадобится)
    // Колонки
    private int finalPumpsCount;           // Итоговое количество колонок
    private int expansionsCount;           // Количество открытых доп. колонок
    private Map<Integer, Double> pumpBusyTime;  // Время работы каждой колонки
    private Map<Integer, Double> pumpLastStartTime; // Время последнего начала работы
    // Доставки
    private int deliveriesCount;            // Количество доставок топлива
    private List<Double> fuelLevels;        // Уровни топлива для среднего
    private double minFuelLevel;             // Минимальный остаток топлива
    // Общее время симуляции
    private double totalSimulationTime;

    public Statistics() {
        this.totalArrivals = 0;
        this.totalServed = 0;
        this.totalRefusals = 0;
        this.waitTimes = new ArrayList<>();
        this.maxWaitTime = 0.0;
        this.serviceTimes = new ArrayList<>();
        this.maxQueueLength = 0;
        this.queueLengths = new ArrayList<>();
        this.finalPumpsCount = 0;
        this.expansionsCount = 0;
        this.pumpBusyTime = new HashMap<>();
        this.pumpLastStartTime = new HashMap<>();
        this.deliveriesCount = 0;
        this.fuelLevels = new ArrayList<>();
        this.minFuelLevel = Double.MAX_VALUE;
        this.totalSimulationTime = 0.0;
    }

     //Запись прибытия автомобиля
    public void recordArrival() {
        totalArrivals++;
    }


    //Запись обслуживания автомобиля
    public void recordService(Car car) {
        totalServed++;

        // Время ожидания
        double waitTime = car.calculateWaitTime();
        waitTimes.add(waitTime);
        if (waitTime > maxWaitTime) {
            maxWaitTime = waitTime;
        }

        // Время обслуживания
        double serviceTime = car.calculateServiceDuration();
        serviceTimes.add(serviceTime);
    }

    //Запись отказа (нехватка топлива)
    public void recordRefusal() {
        totalRefusals++;
    }

    //Запись длины очереди
    public void recordQueueLength(int length, double currentTime) {
        queueLengths.add(length);
        if (length > maxQueueLength) {
            maxQueueLength = length;
        }
    }

    //Запись уровня топлива
    public void recordFuelLevel(double level, double currentTime) {
        fuelLevels.add(level);
        if (level < minFuelLevel) {
            minFuelLevel = level;
        }
    }

    //Запись доставки топлива
    public void recordDelivery() {
        deliveriesCount++;
    }

    //Запись расширения (открытие новой колонки)
    public void recordExpansion() {
        expansionsCount++;
    }

    //Запись начала работы колонки
    public void recordPumpStart(int pumpId, double startTime) {
        pumpLastStartTime.put(pumpId, startTime);
    }

    //Запись окончания работы колонки
    public void recordPumpEnd(int pumpId, double endTime) {
        if (pumpLastStartTime.containsKey(pumpId)) {
            double startTime = pumpLastStartTime.get(pumpId);
            double busyDuration = endTime - startTime;

            double currentBusyTime = pumpBusyTime.getOrDefault(pumpId, 0.0);
            pumpBusyTime.put(pumpId, currentBusyTime + busyDuration);

            // Удаляем запись о начале, чтобы не учитывать повторно
            pumpLastStartTime.remove(pumpId);
        }
    }

    //Установка итогового количества колонок
    public void setFinalPumpsCount(int count) {
        this.finalPumpsCount = count;
    }

    //Установка общего времени симуляции
    public void setTotalSimulationTime(double time) {
        this.totalSimulationTime = time;
    }

    //Получить среднее время ожидания
    public double getAverageWaitTime() {
        if (waitTimes.isEmpty()) return 0.0;
        double sum = 0.0;
        for (double wt : waitTimes) {
            sum += wt;
        }
        return sum / waitTimes.size();
    }

    //Получить среднее время обслуживания
    public double getAverageServiceTime() {
        if (serviceTimes.isEmpty()) return 0.0;
        double sum = 0.0;
        for (double st : serviceTimes) {
            sum += st;
        }
        return sum / serviceTimes.size();
    }

    //Получить средний остаток топлива
    public double getAverageFuelLevel() {
        if (fuelLevels.isEmpty()) return 0.0;
        double sum = 0.0;
        for (double level : fuelLevels) {
            sum += level;
        }
        return sum / fuelLevels.size();
    }

    //Получить загруженность каждой колонки
    public Map<Integer, Double> getPumpUtilizations() {
        Map<Integer, Double> utilizations = new HashMap<>();

        if (totalSimulationTime == 0) return utilizations;

        for (Map.Entry<Integer, Double> entry : pumpBusyTime.entrySet()) {
            int pumpId = entry.getKey();
            double busyTime = entry.getValue();
            double utilization = (busyTime / totalSimulationTime) * 100.0;
            utilizations.put(pumpId, utilization);
        }

        return utilizations;
    }
    // ============= ГЕТТЕРЫ ДЛЯ ВСЕХ ПОЛЕЙ =============

    public int getTotalArrivals() { return totalArrivals; }
    public int getTotalServed() { return totalServed; }
    public int getTotalRefusals() { return totalRefusals; }
    public double getMaxWaitTime() { return maxWaitTime; }
    public int getMaxQueueLength() { return maxQueueLength; }
    public int getFinalPumpsCount() { return finalPumpsCount; }
    public int getExpansionsCount() { return expansionsCount; }
    public int getDeliveriesCount() { return deliveriesCount; }
    public double getMinFuelLevel() { return minFuelLevel; }

    //Вывод отчета в консоль
    public void printReport() {
        System.out.println("\n" + "=".repeat(60));
        System.out.println(" СТАТИСТИЧЕСКИЙ ОТЧЁТ");
        System.out.println("=".repeat(60));
        System.out.println("  Всего прибыло автомобилей: " + totalArrivals);
        System.out.println("  Обслужено автомобилей: " + totalServed);
        System.out.println("  Отказано (нехватка топлива): " + totalRefusals);
        System.out.printf("  Среднее время ожидания: %.2f мин\n", getAverageWaitTime());
        System.out.printf("  Максимальное время ожидания: %.2f мин\n", maxWaitTime);
        System.out.printf("  Среднее время обслуживания: %.2f мин\n", getAverageServiceTime());
        System.out.println("  Максимальная длина очереди: " + maxQueueLength);
        System.out.println("  Итоговое количество колонок: " + finalPumpsCount);
        System.out.println("  Количество открытых доп. колонок: " + expansionsCount);
        System.out.println("  Количество доставок: " + deliveriesCount);
        System.out.printf("  Средний остаток топлива: %.2f л\n", getAverageFuelLevel());
        System.out.printf("  Минимальный остаток топлива: %.2f л\n", minFuelLevel);
        System.out.println("\n ЗАГРУЖЕННОСТЬ КОЛОНОК:");
        Map<Integer, Double> utilizations = getPumpUtilizations();
        if (utilizations.isEmpty()) {
            System.out.println("  Нет данных о загруженности колонок");
        } else {
            for (Map.Entry<Integer, Double> entry : utilizations.entrySet()) {
                System.out.printf("  Колонка #%d: %.2f%%\n", entry.getKey(), entry.getValue());
            }
        }

        System.out.println("\n" + "=".repeat(60));
    }
    //Сброс статистики
    public void reset() {
        totalArrivals = 0;
        totalServed = 0;
        totalRefusals = 0;

        waitTimes.clear();
        maxWaitTime = 0.0;
        serviceTimes.clear();

        maxQueueLength = 0;
        queueLengths.clear();

        finalPumpsCount = 0;
        expansionsCount = 0;
        pumpBusyTime.clear();
        pumpLastStartTime.clear();

        deliveriesCount = 0;
        fuelLevels.clear();
        minFuelLevel = Double.MAX_VALUE;

        totalSimulationTime = 0.0;
    }
}