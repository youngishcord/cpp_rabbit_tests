/*
Кастомная очередь внутри программы для передачи информации между тредами.
Основная задача - передача команд в обработчик, который висит в отдельном потоке и выполняет
действия по обработке данных.
*/

// Класс для безопасной очереди задач между потоками
template <typename T>
class ThreadSafeQueue
{
public:
    void push(T value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        // опять же передать во владение очереди полученную сущность, в этом случае таску
        queue_.push(std::move(value));
        condition_.notify_one();
    }

    // берет указатель на полученный объект заполняет объект данными из очереди
    bool try_pop(T &value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty())
        {
            return false;
        }
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::queue<T> queue_;
    std::condition_variable condition_;
};