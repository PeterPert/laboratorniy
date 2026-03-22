package org.example;

public class Main {
    public static void main(String[] args) {
        Config config = new Config();
        printConfigInfo(config);
        Simulation simulation = new Simulation(config);
        simulation.run();
        System.out.println(" ИТОГОВАЯ СТАТИСТИКА");
        System.out.println("=".repeat(60));

        Statistics stats = simulation.getStatistics();
        stats.printReport();
    }

    public static void printConfigInfo(Config config) {
        System.out.println("==========================================");
        System.out.println("   СИМУЛЯЦИЯ РАБОТЫ АВТОЗАПРАВОЧНОЙ СТАНЦИИ");
        System.out.println("==========================================");
        System.out.println("\n ПАРАМЕТРЫ СИМУЛЯЦИИ:");
        System.out.println("------------------------------------------");
        System.out.printf("Длительность симуляции: %d дней\n", config.getSimulationDays());
        System.out.printf("Начальное количество колонок: %d\n", config.getInitialPumps());
        System.out.printf("Максимальное количество колонок: %d\n", config.getMaxPumps());
        System.out.printf("Скорость заправки: %.1f л/мин\n", config.getDefaultFlowRate());
        System.out.printf("Порог ожидания для расширения: %.1f мин\n", config.getQueueThresholdMinutes());
        System.out.printf("Задержка расширения: %d дня(ей)\n", config.getExpansionDelayDays());
        System.out.printf("Начальный запас топлива: %.0f л\n", config.getInitialFuel());
        System.out.printf("Максимальная ёмкость хранилища: %.0f л\n", config.getMaxFuelCapacity());
        System.out.printf("Интервал доставки: %.1f ч\n", config.getDeliveryIntervalHours());
        System.out.printf("Объём доставки: %.0f л\n", config.getDeliveryVolume());
        System.out.printf("Время разгрузки: %.0f мин\n", config.getDeliveryDurationMinutes());
        System.out.printf("Сид генератора: %d\n", config.getRandomSeed());
        System.out.println("==========================================\n");
    }
}
