DELETE FROM `Basket`;

DELETE FROM `Product`;

DELETE FROM `User`;


INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(1, 'Qwerty', 'Qwerty', 'Qwerty', 'Qwerty', 'Qwerty@mail.ru')
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(2, '_12345', '_12345', '_12345', '_12345', '_12345@gmail.com')
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(3, 'flower', 'flower', 'flower', 'flower', 'flower@mail.ru')
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(4, 'me', 'me', 'me', 'me', 'me@gmail.com')
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(5, 'he', 'he', 'he', 'he', 'he@mail.ru')
;

INSERT INTO `Product`
(id, product_name, product_category, product_content, creator_id, create_date)
VALUES(1, 'doll', 'toy', 'Barbie_doll', 3, NOW())
;

INSERT INTO `Product`
(id, product_name, product_category, product_content, creator_id, create_date)
VALUES(2, 'boll', 'toy', 'kolobok', 1, NOW())
;

INSERT INTO `Product`
(id, product_name, product_category, product_content, creator_id, create_date)
VALUES(3, 'dress', 'cloth', 'for_those_who_love_themselves', 5, NOW())
;

INSERT INTO `Product`
(id, product_name, product_category, product_content, creator_id, create_date)
VALUES(4, 'flover', 'flover', 'beautiful', 4, NOW())
;

INSERT INTO `Product`
(id, product_name, product_category, product_content, creator_id, create_date)
VALUES(5, 'knife', 'kitchenware', 'very_sharp_one', 2, NOW())
;

INSERT INTO `Basket`
(user_id, product_id)
VALUES(1, 1)
;

INSERT INTO `Basket`
(user_id, product_id)
VALUES(2, 3)
;

INSERT INTO `Basket`
(user_id, product_id)
VALUES(3, 5)
;

INSERT INTO `Basket`
(user_id, product_id)
VALUES(4, 4)
;

INSERT INTO `Basket`
(user_id, product_id)
VALUES(5, 2)
;
