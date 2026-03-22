package org.example;
import java.util.*;
import java.util.ArrayList;
import java.util.Queue;

import java.util.*;

public class GasStation {
    private List<FuelPump> pumps;           // Список колонок
    private Queue<Car> queue;                // Очередь ожидающих автомобилей (FIFO)
    private double fuelReserve;               // Текущий запас топлива на станции
    private final double maxFuelCapacity;     // Максимальная ёмкость хранилища
    private double lastDeliveryTime;          // Время последней доставки
    private double deliveryInterval;          // Как часто приезжает бензовоз (в минутах)
    private double deliveryVolume;            // Сколько литров привозит бензовоз

    // Конструктор
    public GasStation(Config config) {
        this.pumps = new ArrayList<>();
        for (int i = 0; i < config.getInitialPumps(); i++) {
            pumps.add(new FuelPump(config.getDefaultFlowRate()));
        }
        this.queue = new LinkedList<>();
        this.fuelReserve = config.getInitialFuel();
        this.maxFuelCapacity = config.getMaxFuelCapacity();
        this.lastDeliveryTime = 0.0;
        this.deliveryInterval = config.getDeliveryIntervalHours() * 60; // часы → минуты
        this.deliveryVolume = config.getDeliveryVolume();
    }

    // ============= ГЕТТЕРЫ =============

    public List<FuelPump> getPumps() {
        return pumps;
    }

    public Queue<Car> getQueue() {
        return queue;
    }

    public double getFuelReserve() {
        return fuelReserve;
    }

    public double getMaxFuelCapacity() {
        return maxFuelCapacity;
    }

    public double getLastDeliveryTime() {
        return lastDeliveryTime;
    }

    public double getDeliveryInterval() {
        return deliveryInterval;
    }

    public double getDeliveryVolume() {
        return deliveryVolume;
    }

    // ============= СЕТТЕРЫ =============

    public void setDeliveryInterval(double deliveryIntervalHours) {
        this.deliveryInterval = deliveryIntervalHours * 60;
    }

    public void setDeliveryVolume(double deliveryVolume) {
        this.deliveryVolume = deliveryVolume;
    }

    public void setLastDeliveryTime(double lastDeliveryTime) {
        this.lastDeliveryTime = lastDeliveryTime;
    }

    // ============= МЕТОДЫ ДЛЯ РАБОТЫ С КОЛОНКАМИ =============
    //Найти первую свободную колонку
    public FuelPump findFreePump() {
        for (FuelPump pump : pumps) {
            if (!pump.isBusy()) {
                return pump;
            }
        }
        return null;
    }

    //Проверить, есть ли свободная колонка
    public boolean hasFreePump() {
        return findFreePump() != null;
    }

    //Получить общее количество колонок
    public int getTotalPumpsCount() {
        return pumps.size();
    }

    //Получить колонку, на которой обслуживается автомобиль
    public FuelPump getPumpForCar(Car car) {
        for (FuelPump pump : pumps) {
            if (pump.isBusy() && pump.getCurrentCar() != null &&
                    pump.getCurrentCar().getId() == car.getId()) {
                return pump;
            }
        }
        return null;
    }

    // ============= МЕТОДЫ ДЛЯ РАБОТЫ С ОЧЕРЕДЬЮ =============

    //Добавить автомобиль в очередь
    public void addToQueue(Car car) {
        queue.offer(car);
    }

    //Взять автомобиль из очереди (FIFO)
    public Car pollFromQueue() {
        return queue.poll();
    }

    //Получить размер очереди
    public int getQueueSize() {
        return queue.size();
    }

    //Проверить, пуста ли очередь
    public boolean isQueueEmpty() {
        return queue.isEmpty();
    }

    //Очистить очередь
    public void clearQueue() {
        queue.clear();
    }

    // ============= МЕТОДЫ ДЛЯ РАБОТЫ С ТОПЛИВОМ =============

    //Уменьшить запас топлива
    public void decreaseFuelReserve(double amount) {
        if (amount <= fuelReserve) {
            fuelReserve -= amount;
        } else {
            fuelReserve = 0.0;
        }
    }

    //Увеличить запас топлива (с учётом максимальной ёмкости)
    public void increaseFuelReserve(double amount) {
        fuelReserve = Math.min(fuelReserve + amount, maxFuelCapacity);
    }

    //Проверить, достаточно ли топлива
    public boolean hasEnoughFuel(double required) {
        return fuelReserve >= required;
    }

    // ============= МЕТОДЫ ДЛЯ РАБОТЫ С ДОСТАВКОЙ =============

    //Обработать доставку топлива
    public void processDelivery(double currentTime) {
        double oldReserve = fuelReserve;
        increaseFuelReserve(deliveryVolume);
        System.out.printf("   Доставка: было %.1f, стало %.1f\n", oldReserve, fuelReserve);
        lastDeliveryTime = currentTime;
    }

    // ============= МЕТОДЫ ДЛЯ ЗАПРАВКИ =============
    //Попытаться заправить автомобиль
    public boolean tryRefuelCar(Car car, double currentTime) {
        if (!hasEnoughFuel(car.getDesiredFuel())) {
            return false;
        }
        // Ищем свободную колонку
        FuelPump freePump = findFreePump();
        if (freePump == null) {
            return false;
        }
        startService(car, freePump, currentTime);
        return true;
    }

    //Начать обслуживание автомобиля на колонке
    public void startService(Car car, FuelPump pump, double currentTime) {
        pump.assignCar(car, currentTime);
        decreaseFuelReserve(car.getDesiredFuel());
    }

    // ============= МЕТОД ДЛЯ ОТКРЫТИЯ НОВОЙ КОЛОНКИ =============
    //Открыть новую колонку с заданной скоростью
    public FuelPump openNewPump(double flowRate, double currentTime, int day) {
        FuelPump newPump = new FuelPump(flowRate, day);
        pumps.add(newPump);
        return newPump;
    }

    @Override
    public String toString() {
        return String.format("GasStation{pumps=%d, queue=%d, fuel=%.1f/%.1f, lastDelivery=%.1f}",
                pumps.size(), queue.size(), fuelReserve, maxFuelCapacity, lastDeliveryTime);
    }
}