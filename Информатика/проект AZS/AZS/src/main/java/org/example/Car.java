package org.example;
import java.util.Random;

public class Car {
//    private static int nextId = 1;
//    private static Random random = new Random();
//    private final int id;
//    private final double tankCapacity;
//    private final double fuelLevel;
//    private final double desiredFuel;
//    private double arrivalTime;
//    private double startServiceTime;
//    private double endServiceTime;
//
//    // Конструктор с генерацией случайных параметров
//    public Car(Random random) {
//        this.id = nextId++;
//        this.tankCapacity = generateTankCapacity();
//        this.fuelLevel = generateFuelLevel(tankCapacity);
//        this.desiredFuel = generateDesiredFuel(tankCapacity, fuelLevel);
//        this.arrivalTime = 0.0;
//        this.startServiceTime = 0.0;
//        this.endServiceTime = 0.0;
//    }
//
//    // ============= ГЕНЕРАТОРЫ ЗНАЧЕНИЙ =============
//
//    private double generateTankCapacity() {
//        double[] capacities = {40, 50, 60, 70, 80};
//        return capacities[random.nextInt(capacities.length)];
//    }
//
//    private double generateFuelLevel(double tankCapacity) {
//        double minFuel = tankCapacity * 0.1;  // 10%
//        double maxFuel = tankCapacity * 0.9;  // 90%
//        return minFuel + (maxFuel - minFuel) * random.nextDouble();
//    }
//
//    private double generateDesiredFuel(double tankCapacity, double fuelLevel) {
//        double maxPossibleFuel = tankCapacity - fuelLevel; // свободное место
//        double desired = 5 + (maxPossibleFuel - 5) * random.nextDouble(); // от 5 до максимума
//
//        return Math.min(desired, maxPossibleFuel);
//    }

    /**
     если нужны одинаковые генерации то берем то что ниже, если нужно разные, то берем то что выше
     */
private static int nextId = 1;
    private final int id;
    private final double tankCapacity;
    private final double fuelLevel;
    private final double desiredFuel;
    private double arrivalTime;
    private double startServiceTime;
    private double endServiceTime;

    public Car(Random random) { // принимаем Random
        this.id = nextId++;
        this.tankCapacity = generateTankCapacity(random);
        this.fuelLevel = generateFuelLevel(tankCapacity, random);
        this.desiredFuel = generateDesiredFuel(tankCapacity, fuelLevel, random);
        this.arrivalTime = 0.0;
        this.startServiceTime = 0.0;
        this.endServiceTime = 0.0;
    }

    private double generateTankCapacity(Random random) {
        double[] capacities = {40, 50, 60, 70, 80};
        return capacities[random.nextInt(capacities.length)];
    }

    private double generateFuelLevel(double tankCapacity, Random random) {
        double minFuel = tankCapacity * 0.1;
        double maxFuel = tankCapacity * 0.9;
        return minFuel + (maxFuel - minFuel) * random.nextDouble();
    }

    private double generateDesiredFuel(double tankCapacity, double fuelLevel, Random random) {
        double maxPossibleFuel = tankCapacity - fuelLevel;
        double desired = 5 + (maxPossibleFuel - 5) * random.nextDouble();
        return Math.min(desired, maxPossibleFuel);
    }
    // ============= ГЕТТЕРЫ =============

    public int getId() {
        return id;
    }

    public double getTankCapacity() {
        return tankCapacity;
    }

    public double getFuelLevel() {
        return fuelLevel;
    }

    public double getDesiredFuel() {
        return desiredFuel;
    }

    public double getArrivalTime() {
        return arrivalTime;
    }

    public double getStartServiceTime() {
        return startServiceTime;
    }

    public double getEndServiceTime() {
        return endServiceTime;
    }

    // ============= СЕТТЕРЫ =============

    public void setArrivalTime(double arrivalTime) {
        this.arrivalTime = arrivalTime;
    }

    public void setStartServiceTime(double startServiceTime) {
        this.startServiceTime = startServiceTime;
    }

    public void setEndServiceTime(double endServiceTime) {
        this.endServiceTime = endServiceTime;
    }

    // ============= МЕТОДЫ ДЛЯ РАСЧЕТОВ =============
     //Вычислить время ожидания
    public double calculateWaitTime() {
        // Если машина еще не начала заправку, возвращаем 0 (или можно -1 как признак)
        if (startServiceTime == 0.0) {
            return 0.0;
        }
        // Иначе возвращаем разницу (даже если arrivalTime = 0)
        return startServiceTime - arrivalTime;
    }
     //Вычислить время обслуживания
     public double calculateServiceDuration() {
        // Если заправка не закончена, возвращаем 0
        if (endServiceTime == 0.0) {
            return 0.0;
        }
        // Иначе возвращаем разницу (даже если startServiceTime = 0)
        return endServiceTime - startServiceTime;
    }

     //Получить свободное место в баке
    public double getFreeSpace() {
        return tankCapacity - fuelLevel;
    }

    // ============= ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ =============
    //Сброс счетчика ID (для тестирования)
    public static void resetIdCounter() {
        nextId = 1;
    }

    @Override
    public String toString() {
        return String.format("Car{id=%d, tank=%.1f, fuel=%.1f, desired=%.1f, " +
                        "arrival=%.2f, start=%.2f, end=%.2f}",
                id, tankCapacity, fuelLevel, desiredFuel,
                arrivalTime, startServiceTime, endServiceTime);
    }
}