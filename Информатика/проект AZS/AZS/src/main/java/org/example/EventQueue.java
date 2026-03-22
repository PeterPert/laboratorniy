package org.example;

import java.util.*;

public class EventQueue {
    private PriorityQueue<Event> queue;

    public EventQueue() {
        // PriorityQueue автоматически сортирует события по времени
        this.queue = new PriorityQueue<>();
    }

    // Добавить событие в очередь
    public void add(Event event) {
        queue.add(event);
    }

    // Получить следующее событие (самое раннее) и удалить его из очереди
    public Event poll() {
        return queue.poll();
    }

    // Посмотреть следующее событие без удаления
    public Event peek() {
        return queue.peek();
    }

    // Проверить, пуста ли очередь
    public boolean isEmpty() {
        return queue.isEmpty();
    }

    // Получить размер очереди
    public int size() {
        return queue.size();
    }

    // Очистить очередь
    public void clear() {
        queue.clear();
    }

    // Получить все события (для отладки)
    public List<Event> getAllEvents() {
        return new ArrayList<>(queue);
    }

    @Override
    public String toString() {
        return "EventQueue{size=" + queue.size() + "}";
    }
}