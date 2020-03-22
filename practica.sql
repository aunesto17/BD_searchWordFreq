
SHOW search_path;
-- darle el search path de nuestro esquema al query de postgress
SET search_path TO "bd2_practica", information_schema;

""$user",public"


CREATE TABLE categoria
(
  id_categoria  serial                 NOT NULL,
  nom_categoria character varying(255) NOT NULL,
  CONSTRAINT categoria_pkey PRIMARY KEY (id_categoria)
);

CREATE TABLE producto
(
  id_producto 	serial 					NOT NULL,
  nom_producto 	character varying(255) 	NOT NULL,
  CONSTRAINT producto_pkey PRIMARY KEY (id_producto),
  CONSTRAINT producto_id_producto_fkey FOREIGN KEY (categoria)
      REFERENCES categoria (id_categoria) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
);


CREATE TABLE cliente
(
  id_cliente  serial                 PRIMARY KEY,
  nom_cliente character varying(255) NOT NULL,
);

CREATE TABLE ventas
(
  id_venta    serial    PRIMARY KEY,
  id_cliente  integer   REFERENCES cliente,
  id_producto integer   REFERENCES producto,
  cantidad 		INT 	    NOT NULL,
  fecha			  DATE	    NOT NULL,
);

-- insertar 50 categorias
INSERT INTO categoria (id_categoria, nom_categoria)
SELECT x.id, 'categoria_' || x.id
  FROM generate_series(1,50) AS x(id);

-- insertar 3000 productos con categorias al azar(1-50)
INSERT INTO producto (id_producto, nom_producto, id_categoria)
SELECT x.id, 'nom_' || x.id, ceil(random() * 50)
  FROM generate_series(1,3000) AS x(id);

-- insertar 1500 clientes en orden
INSERT INTO cliente (id_cliente, nom_cliente)
SELECT x.id, 'cliente_' || x.id
  FROM generate_series(1,1500) AS x(id);


-- insertar 5 millones de ventas con fechas controladas
INSERT INTO ventas(id_venta, id_cliente, id_producto, cantidad, fecha)
SELECT x.id, ceil(random() * 1500), ceil(random() * 3000), ceil(random() * 500), date '2016-01-01' + (floor(random() * 366)::int )
  FROM generate_series(1,1000000) AS x(id);



CREATE TABLE corpus
(
  id_c        serial PRIMARY KEY,
  palabra_1   character varying(50),
  palabra_2   character varying(50),
  frecuencia  BIGINT, 
)


COPY corpus FROM '/Applications/PostgreSQL 9.4/salida01'


SELECT COUNT(*) FROM corpus;

SELECT * FROM corpus WHERE palabra_1='cat';

CREATE INDEX i_pal1 ON corpus (palabra_1);


SELECT * FROM ventas
WHERE id_cliente = 750;


CREATE INDEX gin_ipal1 ON corpus USING gin (palabra_1) WITH (fastupdate = off);
