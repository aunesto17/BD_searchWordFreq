#!C:\Python34\python
from math import *
import cgi
import cgitb; cgitb.enable()
import psycopg2
import psycopg2.extras
import string
import re
import threading
import time
def normalizar(vector,nvector):
    sumv1=0
    i=0
    tam1=len(vector)
    for pal in vector:
        sumv1=sumv1+pal[1]**2
    sumv1=sqrt(sumv1)
    while (i<tam1):
        nvector.append([vector[i][0],vector[i][1]/sumv1])
        i=i+1

def distanciacos(vector1,vector2):
    i=0
    j=0
    tam1=len(vector1)
    tam2=len(vector2)
    suma=0
    sumv1=1
    sumv2=0
    for pal2 in vector2:
        sumv2=sumv2+pal2[1]**2
    sumv2=sqrt(sumv2)
    while(i<tam1 and j<tam2):
        if(vector1[i][0]<vector2[j][0]):
            i=i+1
        elif(vector1[i][0]>vector2[j][0]):
            j=j+1
        else:
            suma=suma+(vector1[i][1]*vector2[j][1])
            i=i+1
            j=j+1
    return suma/(sumv1*sumv2)

def sacar(recibo,desde,hasta):
    database= psycopg2.connect("dbname=BD2_parcial user=aunesto17 password=Hakerlol1")
    dealer= database.cursor()
    for i in range(desde,hasta):
        dealer.execute(("Select id2,freq from relaciones where id1=%s"),(i,))
        recibo.append(dealer.fetchall())

def word_to_number(p):
    database= psycopg2.connect("dbname=BD2_parcial user=aunesto17 password=Hakerlol1")
    cur = database.cursor()
    lema = "SELECT id FROM lemas WHERE lema='%s';"%p
    cur.execute(lema)
    return cur.fetchall()[0][0]

inicio=time.time()
database= psycopg2.connect("dbname=BD2_parcial user=aunesto17 password=Hakerlol1")
dealer	= database.cursor()
print "Ingrese la palabra: "
palabra = raw_input()
numero = word_to_number(palabra)
print "\n"
dealer.execute(("Select id2,freq from relaciones where id1=%s"),(numero,))
mivector=dealer.fetchall()
nvector=[]
normalizar(mivector,nvector)
mivector=[]
Res=[]
sacar(Res,1,27229)
fin=time.time()
print(fin-inicio)
count=1
distancias=[]
nada=[]
for i in Res:
    if(i!=nada):
        fich=[distanciacos(nvector,i),count]
        distancias.append(fich)
    count=count+1
Res=[]
sacar(Res,27229,54457)
fin=time.time()
print(fin-inicio)
for i in Res:
    if(i!=nada):
        fich=[distanciacos(nvector,i),count]
        distancias.append(fich)
    count=count+1
Res=[]
distancias.sort(reverse=True)
fin=time.time()
lem=0
while lem<100:
    dealer.execute(("Select lema from lemas where id=%s"),(distancias[lem][1],))
    print(dealer.fetchone()[0],"\t",'{:.20f}'.format(distancias[lem][0]))
    lem=lem+1
print(fin-inicio)
distancias=[]
