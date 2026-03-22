package org.example;

import java.util.Random;

public class CarGenerator {
    private final Random random;
    private int totalCarsGenerated;
    private static final double[][] ARRIVAL_RATES = {
            {0, 6, 0.03},    // 00:00 - 06:00: 0.03 авт/мин (≈ 1 авто каждые 33 мин)
            {6, 10, 0.25},   // 06:00 - 10:00: 0.25 авт/мин (≈ 1 авто каждые 4 мин)
            {10, 16, 0.12},  // 10:00 - 16:00: 0.12 авт/мин (≈ 1 авто каждые 8 мин)
            {16, 20, 0.30},  // 16:00 - 20:00: 0.30 авт/мин (≈ 1 авто каждые 3.3 мин)
            {20, 24, 0.08}   // 20:00 - 24:00: 0.08 авт/мин (≈ 1 авто каждые 12.5 мин)
    };

    public CarGenerator(Random random) {
        this.random = random;
        this.totalCarsGenerated = 0;
    }

    //Получить интенсивность прибытия для данного времени
    public double getLambda(double currentTime) {
        double hours = (currentTime / 60.0) % 24;
        for (double[] rate : ARRIVAL_RATES) {
            if (hours >= rate[0] && hours < rate[1]) {
                return rate[2];
            }
        }
        // Если не нашли (например, 24:00), возвращаем ночной тариф
        return 0.12;
    }

    //Генерирует время до следующего автомобиля
    //по экспоненциальному распределению: Δt = -ln(U) / λ
    public double generateNextArrivalTime(double currentTime) {
        double lambda = getLambda(currentTime);
        // Экспоненциальное распределение
        double u = random.nextDouble(); // U ~ Uniform(0, 1)
        double interval = -Math.log(u) / lambda;
        return interval;
    }


    //Создает новый автомобиль с заданным временем прибытия
    public Car generateCar(double arrivalTime) {
        Car car = new Car(random);
        car.setArrivalTime(arrivalTime);
        totalCarsGenerated++;
        return car;
    }

    //Получить общее количество сгенерированных автомобилей
    public int getTotalCarsGenerated() {
        return totalCarsGenerated;
    }
    //Сбросить генератор (для повторного использования)
    public void reset() {
        totalCarsGenerated = 0;
    }

}