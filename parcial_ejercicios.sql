CREATE TABLE personas
(
  nombre  character varying(10) NOT NULL,
  DNI     integer 				NOT NULL,
  ciudad  character varying(10) NOT NULL
);

INSERT INTO personas VALUES ('Renzo',29694064,'Arequipa');
INSERT INTO personas VALUES ('Manuel',29694065,'Lima');
INSERT INTO personas VALUES ('Javier',29694066,'Tacna');
INSERT INTO personas VALUES ('Daniel',29694067,'Arequipa');
INSERT INTO personas VALUES ('Omar',29694068,'Arequipa');
INSERT INTO personas VALUES ('percy',29694069,'Lima');
INSERT INTO personas VALUES ('juan',29694070,'Arequipa');
INSERT INTO personas VALUES ('mario',29694071,'Arequipa');

-- preguntas parcial
5. Nombres de las personas que comieron al menos una pizza en dominos pero que no frecuentan dominos.

SELECT name FROM person
WHERE name NOT IN 
	(SELECT name FROM frequents 
		WHERE name IN 
		(SELECT * FROM eats 
		 INNER JOIN serves
		 ON eats.pizza = serves.pizza
		 WHERE serves.pizzeria = 'dominos'	
		)
	)


SELECT name FROM person




6. Todas las pizzas que solo fueron comidas por personas menores de 24 años o que cuestan menos de $10

SELECT * FROM eats
WHERE name IN
	(SELECT name FROM person
	 INNER JOIN eats
	 ON person.name = eats.name
	 INNER JOIN serves
	 ON eats.pizza = server.pizza
	 WHERE person.age < 24 AND server.price < 10)
ORDER BY name;

-- preguntas otro parcial

2.a. Alumnos que nadie gusta de ellos y que no tienen amigos.

SELECT name FROM highschooler h
LEFT JOIN likes ON h.id = likes.id2
WHERE likes.id2 IS NULL
UNION
SELECT name FROM highschooler h
LEFT JOIN friend ON h.id = friend.id1 OR h.id = friend.id2
WHERE likes.id1 = NULL OR likes.id2 = NULL

2.b A guste de B y B guste de A, mostrar nombre sin duplicados

SELECT DISTINCT h1.name, h2.name FROM highschooler h1, highschooler h2
LEFT JOIN likes l
ON (h1.id = l.id1 AND h2.id = l.id2) OR (h1.id = l.id1 AND h2.id = l.id2)
ORDER BY h1.name
GROUP BY h1.name;

3.b 
SELECT hs.id FROM hs EXCEPT SELECT id1.likes FROM likes


	 



-- Crear un indice clustered en la columna ciudad.
CREATE INDEX ciudad_ind ON personas(ciudad);
CLUSTER personas USING ciudad_ind;



 OPERATOR	    DESCRIPTION
	=			Equal
	>			Greater than
	<			Less than
	>=			Greater than or equal
	<=			Less than or equal
	<> or !=	Not equal
	AND			Logical operator AND
	OR			Logical operator OR


-- Borrar todos las filas de una tabla
DELETE FROM personas;

-- Nos muestra cada elemento de column_1 sin sus repetidos
SELECT DISTINCT column_1 FROM table_name;

-- Nos muestra las combinaciones unicas entre column_1 y column_2
SELECT DISTINCT column_1,column_2 FROM table_name;

-- Nos muestra las combinaciones unicas entre dos columnas, pero elimina duplicados de column_1
SELECT DISTINCT ON (column_1), column_2 FROM table_name
ORDER BY column_1,column_2;

-- Seleccionar registros de una columna, limitandos a 'n' los resultados
SELECT * FROM tabla LIMIT n;



