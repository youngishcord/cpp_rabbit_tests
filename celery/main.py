import celery
from celery import Task

class CustomTask(Task):
	def __init__(self, name, *args, **kwargs):
		super(Task, self).__init__(*args, **kwargs)
		self.name = name

app = celery.Celery(
	"pub",
	broker="amqp://user:pass@localhost:5672//",
	backend="rpc://"
)

task = CustomTask("simple.task").s().set(queue="test")

task.delay("qwer", 12)
