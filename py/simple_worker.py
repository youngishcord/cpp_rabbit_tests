


import celery


app = celery.Celery(
	"worker",
	broker="amqp://user:pass@localhost:5672//",
	backend="rpc://"
)

@app.task(name="simple.ping")
def pong(message, *args):
	print(message)
	return "pong"