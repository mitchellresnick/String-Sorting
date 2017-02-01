all: pointersorter

pointersorter: pointersorter.c
	gcc -Wall -g -o pointersorter pointersorter.c
	#Use ./pointersorter [args]

test:
	./pointersorter "A0a0z0Z"
	./pointersorter "Z0a)324z1432A"
	./pointersorter ""
	./pointersorter "Billy145,./,ann,./,billy..,.3435426Ann    "
	./pointersorter "AAAAA"
	./pointersorter "   aa   a  a   a  n  b"
	./pointersorter "f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0ff00f"
	./pointersorter "A B C D E F G H I J K0L M N O{P}a b c d eE e ee "
	./pointersorter ";wow;;we;;;;rick;;y;"
	./pointersorter " \"what\"?we...did'''it       "
	./pointersorter "!1b@2h#3a%4p"
	./pointersorter "1234234Mitch123 54Sucks...3445   "
	./pointersorter "1243245356437567'/'786'78."
	./pointersorter "'''878I9797 878788''cant,,,..878 /'.;[.think8484...77784of.;;'' 7747964any;].'.' ;[;['/'.more546776 13*()tests..."
	#Examples Given from PDF
	./pointersorter "thing stuff otherstuff blarp"
	./pointersorter "thing1stuff3otherstuff,blarp"
	./pointersorter " aand, aAnd, Aand, AAnd"
	#Test Complete - Results Above

clean:
	rm -f pointersorter
	#Cleaned
