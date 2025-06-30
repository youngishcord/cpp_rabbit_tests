import celery
from celery import Task
import datetime

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

while 1:
	time = str(datetime.datetime.now())
	task.delay("qwer", 12, time)
	# print(time)
