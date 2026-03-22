package org.example;

public class FuelPump {
    private static int nextId = 1;
    private final int id;
    private double flowRate;
    private boolean busy;
    private Car currentCar;
    private int openedAtDay;

    // Конструктор с указанием скорости
    public FuelPump(double flowRate) {
        this.id = nextId++;
        this.flowRate = flowRate;
        this.busy = false;
        this.currentCar = null;
        this.openedAtDay = 0;
    }

    // Конструктор с указанием скорости и дня открытия
    public FuelPump(double flowRate, int openedAtDay) {
        this.id = nextId++;
        this.flowRate = flowRate;
        this.busy = false;
        this.currentCar = null;
        this.openedAtDay = openedAtDay;
    }

    // ============= ГЕТТЕРЫ =============

    public int getId() {
        return id;
    }

    public double getFlowRate() {
        return flowRate;
    }

    public boolean isBusy() {
        return busy;
    }

    public Car getCurrentCar() {
        return currentCar;
    }

    public int getOpenedAtDay() {
        return openedAtDay;
    }

    // ============= СЕТТЕРЫ =============

    public void setFlowRate(double flowRate) {
        this.flowRate = flowRate;
    }

    public void setOpenedAtDay(int openedAtDay) {
        this.openedAtDay = openedAtDay;
    }

    // ============= МЕТОДЫ ДЛЯ РАБОТЫ С КОЛОНКОЙ =============

     //Назначить автомобиль на колонку
    public void assignCar(Car car, double currentTime) {
        this.currentCar = car;
        this.busy = true;
        car.setStartServiceTime(currentTime);
    }


    //Завершить обслуживание
    public double finishService(double currentTime) {
        if (currentCar != null) {
            double endTime = currentCar.getStartServiceTime() +
                    (currentCar.getDesiredFuel() / this.flowRate);
            currentCar.setEndServiceTime(endTime);
            this.currentCar = null;
            this.busy = false;
            return endTime;
        }
        return currentTime;
    }

    // ============= ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ =============
    //Сброс счетчика ID (для тестирования)
    public static void resetIdCounter() {
        nextId = 1;
    }

    @Override
    public String toString() {
        if (currentCar != null) {
            return String.format("FuelPump{id=%d, flowRate=%.1f, busy=true, carId=%d}",
                    id, flowRate, currentCar.getId());
        } else {
            return String.format("FuelPump{id=%d, flowRate=%.1f, busy=false}",
                    id, flowRate);
        }
    }
}