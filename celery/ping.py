import random
import time
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

task = CustomTask("simple.task").s().set(queue="qwer")
ping = CustomTask("simple.ping").s().set(queue="qwer")

# while 1:
time_ = str(datetime.datetime.now())
task.delay("ping", random.randint(0, 100), time_)
# result = ping.delay("ping", random.randint(0, 100), time_).get()
# print(result)
	# time.sleep(5)
