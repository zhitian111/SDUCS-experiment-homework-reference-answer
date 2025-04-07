hdrs = common.h
opts = -g -c
p_src = producer.c
p_obj = producer.o
c_src = consumer.c
c_obj = consumer.o
all: producer consumer
producer: $(p_obj)
	gcc $(p_obj) -o producer
producer.o:$(p_src) $(hdrs)
	gcc $(opts) $(p_src)
consumer.o:$(c_src) $(hdrs)
	gcc $(opts) $(c_src)
consumer: $(c_obj)
	gcc $(c_obj) -o consumer
clean:
	rm producer consumer *.o
