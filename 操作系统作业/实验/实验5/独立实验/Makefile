hdrs = common.h
user_srcs = user.cpp
user_objs = user.o
barbershop_srcs = barbershop.cpp
barbershop_objs = barbershop.o
barber_srcs = barber.cpp
barber_objs = barber.o
all: user barbershop barber
$(user_objs): $(user_srcs) $(hdrs)
	g++ -c $(user_srcs) -o $(user_objs)
user: $(user_objs)
	g++ -o user $(user_objs)
$(barbershop_objs): $(barbershop_srcs) $(hdrs)
	g++ -c $(barbershop_srcs) -o $(barbershop_objs)
barbershop: $(barbershop_objs)
	g++ -o barbershop $(barbershop_objs)
$(barber_objs): $(barber_srcs) $(hdrs)
	g++ -c $(barber_srcs) -o $(barber_objs)
barber: $(barber_objs)
	g++ -o barber $(barber_objs)
clean:
	rm user *.o barbershop 
