package org.example;

public class Config {
    private int simulationDays = 7;
    private int initialPumps = 2;
    private int maxPumps = 10;
    private double defaultFlowRate = 20.0;  //должно быть 20
    private double queueThresholdMinutes = 12.0;
    private int expansionDelayDays = 2;
    private double initialFuel = 10000.0;
    private double maxFuelCapacity = 15000.0;
    private double deliveryIntervalHours = 24.0;
    private double deliveryVolume = 10000.0;
    private double deliveryDurationMinutes = 30.0;
    private long randomSeed = 100;

    // Геттеры
    public int getSimulationDays() { return simulationDays; }
    public int getInitialPumps() { return initialPumps; }
    public int getMaxPumps() { return maxPumps; }
    public double getDefaultFlowRate() { return defaultFlowRate; }
    public double getQueueThresholdMinutes() { return queueThresholdMinutes; }
    public int getExpansionDelayDays() { return expansionDelayDays; }
    public double getInitialFuel() { return initialFuel; }
    public double getMaxFuelCapacity() { return maxFuelCapacity; }
    public double getDeliveryIntervalHours() { return deliveryIntervalHours; }
    public double getDeliveryVolume() { return deliveryVolume; }
    public double getDeliveryDurationMinutes() { return deliveryDurationMinutes; }
    public long getRandomSeed() { return randomSeed; }
}