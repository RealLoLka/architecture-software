# Компонентная архитектура
<!-- Состав и взаимосвязи компонентов системы между собой и внешними системами с указанием протоколов, ключевые технологии, используемые для реализации компонентов.
Диаграмма контейнеров C4 и текстовое описание. 
-->
## Компонентная диаграмма

```plantuml
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml

AddElementTag("microService", $shape=EightSidedShape(), $bgColor="CornflowerBlue", $fontColor="white", $legendText="microservice")
AddElementTag("storage", $shape=RoundedBoxShape(), $bgColor="lightSkyBlue", $fontColor="white")

Person(admin, "Администратор")
Person(moderator, "Модератор")
Person(user, "Пользователь")

System_Ext(web_site, "Клиентский веб-сайт", "HTML, CSS, JavaScript, React", "Веб-интерфейс")

System_Boundary(online_store, "Сайт магазин") {
   'Container(web_site, "Клиентский веб-сайт", ")
   Container(client_service, "Сервис авторизации", "C++", "Сервис управления пользователями", $tags = "microService")    
   Container(product_service, "Сервис товаров", "C++", "Сервис управления блогами", $tags = "microService") 
   Container(basket_service, "Сервис корзины", "C++", "Сервис управления постами", $tags = "microService")   
   ContainerDb(db, "База данных", "MySQL", "Хранение данных о блогах, постах и пользователях", $tags = "storage")
   
}

Rel(admin, web_site, "Просмотр, добавление и редактирование информации о пользователях, опубликованных товаров")
Rel(moderator, web_site, "Редактирование информации о пользователях и товарах, решение проблем с корзиной")
Rel(user, web_site, "Регистрация, просмотр товаров и добавление их в корзину")

Rel(web_site, client_service, "Работа с пользователями", "localhost/person")
Rel(client_service, db, "INSERT/SELECT/UPDATE", "SQL")

Rel(web_site, product_service, "Работа с товарами", "localhost/pres")
Rel(product_service, db, "INSERT/SELECT/UPDATE", "SQL")

Rel(web_site, basket_service, "Работа с корзиной", "localhost/conf")
Rel(basket_service, db, "INSERT/SELECT/UPDATE", "SQL")

@enduml
```
## Список компонентов  

### Сервис авторизации
**API**:
-	Создание нового пользователя
      - входные параметры: login, пароль, имя, фамилия, email.
      - выходные параметры: отсутствуют
-	Поиск пользователя по логину
     - входные параметры:  login
     - выходные параметры: имя, фамилия, email.
-	Поиск пользователя по маске имени и фамилии
     - входные параметры: маска фамилии, маска имени
     - выходные параметры: login, имя, фамилия, email.

### Сервис товаров
**API**:
- Создание товара
  - Входные параметры: название товара, категория, характеристики, продавец.
  - Выходыне параметры: идентификатор товара
- Получение списка всех товаров
  - Входные параметры: отсутствуют
  - Выходные параметры: массив товаров, где для каждого указаны его идентификатор, название, категория, характеристики, продавец.

### Сервис корзины
**API**:
- Добавление товара в корзину
  - Входные параметры: идентификатор товара
  - Выходные параметры: отсутствуют
- Получение корзины
  - Входные параметры: отсутствуют
  - Выходные параметры: массив товаров добавленных в корзину, где указаны его идентификатор, название, категория, характеристики, продавец.
