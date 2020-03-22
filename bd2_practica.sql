SET search_path TO "bd2_practica", information_schema;

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
  id_categoria integer REFERENCES categoria
);


CREATE TABLE cliente
(
  id_cliente  serial                 PRIMARY KEY,
  nom_cliente character varying(255) NOT NULL
);


CREATE TABLE ventas
(
  id_cliente  integer REFERENCES cliente,
  id_producto integer REFERENCES producto,
  cantidad 		INT 	  NOT NULL,
  fecha			  DATE	 NOT NULL,
  PRIMARY KEY(id_cliente,id_producto)
);


INSERT INTO categoria (id_categoria, nom_categoria)
SELECT x.id, 'categoria_' || x.id
  FROM generate_series(1,50) AS x(id);


INSERT INTO producto (id_producto, nom_producto, id_categoria)
SELECT x.id, 'nom_' || x.id, ceil(random() * 50)
  FROM generate_series(1,3000) AS x(id);

INSERT INTO cliente (id_cliente, nom_cliente)
SELECT x.id, 'cliente_' || x.id
  FROM generate_series(1,1500) AS x(id

SELECT * FROM ventas
WHERE id_cliente = 750;

0. SIN INDICE (t = 7749 ms)
1. INDICE NORMAL cliente (t = 1945, 1454, 1467, 1458 ms)
2. INDICE CLUSTERED cliente (t= 1439, 1443, 1481, 1457 ms)
3. INDEXAR TODA LA TABLA ()

CREATE INDEX ventas_cliente ON ventas(id_cliente); (157305 ms.)

DROP INDEX ventas_cliente;

CLUSTER ventas_cliente ON ventas; (306266 ms.)

CREATE INDEX whole_ventas ON ventas(id_venta,id_producto,cantidad,fecha); (142571 ms.)

CREATE INDEX whole_ventas ON ventas(id_venta,id_cliente,id_producto,cantidad,fecha); (150512 ms.)

SELECT * FROM ventas
  WHERE id_cliente = 750 AND id_producto = 1706 AND cantidad = 172 AND fecha = '2016-01-09'; (6615 ms.)


SELECT * FROM ventas
  WHERE id_cliente = 800 AND id_producto = 201 AND cantidad = 190 AND fecha = '2016-01-12';


SHOW hba_file;