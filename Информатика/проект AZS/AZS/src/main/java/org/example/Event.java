package org.example;

public class Event implements Comparable<Event> {
    public enum Type {
        ARRIVAL,        // прибытие автомобиля
        SERVICE_END,    // окончание заправки
        FUEL_DELIVERY,  // доставка топлива
        PUMP_OPEN       // открытие новой колонки
    }
    private final Type type;
    private final double time;
    private Car car;
    private FuelPump pump;

    public Event(Type type, double time) {
        this.type = type;
        this.time = time;
    }

    public Event(Type type, double time, Car car) {
        this.type = type;
        this.time = time;
        this.car = car;
    }

    public Event(Type type, double time, Car car, FuelPump pump) {
        this.type = type;
        this.time = time;
        this.car = car;
        this.pump = pump;
    }

    public Type getType() { return type; }
    public double getTime() { return time; }
    public Car getCar() { return car; }
    public FuelPump getPump() { return pump; }

    @Override
    public int compareTo(Event other) {
        return Double.compare(this.time, other.time);
    }

    @Override
    public String toString() {
        return String.format("Event{type=%s, time=%.2f}", type, time);
    }
}