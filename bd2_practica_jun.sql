CREATE FUNCTION Zero(val integer) RETURN integer AS $$
BEGIN
	IF val > 0 THEN
	RAISE NOTICE 'el numero es mayor que cero';
	END IF;

	IF val < 0 THEN
	RAISE NOTICE 'el numero es menor que cero';
	END IF;

	IF val = 0 THEN
	RAISE NOTICE 'el numero es cero';
	END IF
END$$
RETURN 


SELECT * FROM relaciones WHERE id1 = 1685 OR id1 = 42365 OR id1 = 36880 OR id1 =  49120 OR id1 = 20551 OR id1=14529 OR id1=20294 OR id1=50491;

DELETE FROM relaciones20 WHERE id2 <> 1685;