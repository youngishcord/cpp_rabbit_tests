

ref: https://blog.petrzemek.net/2017/06/25/consuming-and-publishing-celery-tasks-in-cpp-via-amqp/
ref: https://cppcooking.blogspot.com/2022/12/rabbitmq-c-client-1.html

examples: https://github.com/bobeff/rabbitmq-cpp-tutorials

## Обработка полученных сообщений
Фактически мне нет нужды создавать кучу функций с декораторами, как в питоне,
достаточно получить сообщение задачи, прочитать ее имя и выполнить необходимые действия.
