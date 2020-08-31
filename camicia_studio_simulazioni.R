# Camicia

rm(list = ls())
graphics.off()

# Simulazione di 1 mln di partite

dati = read.table('camicia_simulazione_1mln_partite.txt', header = TRUE)
attach(dati)

t = table(Vincitore)
t
# Il numero di partite vinte tende a essere uguale per G1 e G2

summary(NCarte)

dev.new()
hist(NCarte, prob = TRUE, main = "N° simulazioni = 1 mln")
x = 0:10^6
y = dexp(x, rate = 1/mean(NCarte))
lines(x, y)
# La distribuzione può essere approssimata con un'esponenziale di parametro lambda = 1/(media numero di carte)
# VERIFICA (O CONFUTAZIONE) ANALITICA?

detach(dati)
