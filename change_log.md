  Разработка нашего проекта началась с выбора игры. Пока одни выбирали шахматы, другие - морской мой, некоторые даже не думали начинать;
  мы же остановились на весьма популярной игре - "Memo". Суть её заключается в нахождении пары карт с одинаковым изображением. Почему мы
  выбрали именно эту игру? Вопрос вполне уместный, однако, ответ будет не так уж и красноречив... Потому что! Просто вспомнили о ней и сразу
  же(нет) взялись за ее разработку.
  
  Первые версии нашего проекта несли характер настройки среды программирования и удаленного хранилища. Была совершена серия тестовых
  коммитов, после которых было принято решение полностью перейти на разработку под ОС Windows. Сделали мы так исключительно ради  
  уменьшения хлопот, которых бы мы не смогли избежать. Не самое хорошее решение, но на момент старта работ оно казалось наиболее оптимальным.
  
  Все это было в самом начале, когда мы только создали первое окно и осознали, что не сможем использовать Simple_window и непосредственно
  сам Window, так как нуждались в окне, способном грамотно работать с нашими данными. Однако на данном этапе нам хватало Window, который мы 
  успешно использовали. Для того, чтобы видеть, как изображения и виджеты крепятся к окну (пропорции, взаимное положение и т.д.), 
  мы создали временный класс grid, наследованный от Graph_lib::Lines.

  И вот, наконец-то, мы начали писать код игры. Первым шагом мы постарались определить, какие ресурсы для этого нам потребуются. Так как
  игра должна была содержать в себе множество изображений, нам потребовалось решить две принципиальные задачи: хранение и доступ к
  изображениям, их дальнейшая обработка. На этом этапе мы столкнулись с проблемой, вероятнее всего связанной с FLTK: мы не могли получить 
  доступ к изображениям через относительные пути (они не отрисовывались). Поэтому нам пришлось, используя макросы, определять обсолютный 
  путь до файлов игры, а затем, используя его, находить папку с нашими изображениями.
  
  Затем наметились следующие задачи. Дело в том, что с самого начала мы решили писать игру, которая будет работать в режиме fullscreen.
  Это повлекло за собой одну проблему: различные устройства обладают различными разрешениями. Даже наши компьютеры имели разрешения 1920x1080
  и 1280x720. Мы используем изображения и окно фиксированного размера, а, значит, при переносе с большего разрешения на меньшее картинки могли 
  отображаться некорректно: выходить за рамки экрана, растягиваться и т.д. В FLTK имеется метод, переводящий окно в режим fullscreen, но 
  проблемы с картинками это не решает. Поэтому нам понадобилась функция, получающая размеры экрана, и "что-то", что меняло бы картинки в 
  соответствии с ними. Функцию мы взяли с ресурса stack_overflow, хотя, оказывается, она была встроена в FLTK. Урезание картинок было 
  поручено скрипту на python, использующего библиотеку pillow.
  
  Первый коммит вызывает незабываемые ощущения. Первый мерчь - ощущения, которые невозможно забыть. Настал тот момент, когда нам пришлось
  объединтять наш код в одно целое, чтоб не отставать друг от друга. Опять пошли проблемы с настройками проектов, с сохранениями 
  коммитов и сихронизацией файлов. Пара ****ing commit и всё заработало. Ну, почти. При попытке запустить то, что уже работало на одном 
  устройстве, на другом вызывало ряд непонятных ошибок. Как оказалось, они были связаны с отсутствием библиотеки pillow и собственно самого 
  питона. На устранение данной ошибки ушло большое количество времени сравнимое со временем первичной настройки проекта.
  
  Львиную долю нашей игры занимают кнопки. В FLTK они, по нашему скромному мнению, реализованы <strike> как гавно </strike> не самым хорошим
  образом. Поэтому на начальном этапе у нас были большие проблемы с ними. Создание объекта, его отрисовка, обработка нажатия и т.д. Однако 
  это потребовало длительных раздумий над структуой классов и вариациями наследования. Эти проблемы приследовали нас на протяжение всей 
  работы.
  
  Однако были два класса, которые так или иначе должны были присутствовать в игре: Card и Field. Поэтому разработка началась с них. Через 
  некоторое время мы добились того, что при помощи огромного количества костылей окно открывалось, к нему привязывался Field с несколькими заранее предустановленным тестовыми карточками. Это был важный шаг, так как
  от этого можно было отталкиваться, убирая со временем костыли, делая программу более универсальной. Хотя, конечно, в тот момент, игрой
  её назвать было сложно, ведь она не имела никакого смысла.
  
  Поэтому перед тем как завести речь об этом алгоритме, необходимо понять, что из себя представляет игра. В основе игры лежит задача 
  отыскать все пары карточек с одинаковыми изображениями. Такого определения должно хватило для того, чтоб начать что-либо писать. Далее
  немного о деталях. Мы определили фундаментальный для нашего проекта класс - Card. Объект этого класса представляет из себя кнопку и изображение, 
  рисующееся поверх кнопки. Наследовать мы его решили от Graph_lib::Rectangle. Это было сделано по той причине, что, по сути, карточка
  в большой степени имеет смысл прямоугольника, и первое, что отрисовывается в ней, - именно прямогуольник. Хотя можно было наследовать
  карточку и от Image, и от Button. 
  
  Дальше идет класс Field - скорее всего самый важный класс по причине того, что он хранит в себе массив из карточек, инициализирует их,
  генерирует случайным образом пару карт, определяя, какую картинку они должны отображать. Наследовать его нужно было от Window, пока мы
  не написали собственное окно. Причины этого, с одной стороны, очевидны, а с другой - можно задуматься, зачем это нужно. Давайте 
  рассмотрим логику нашего окна. 
  
  Оно является элементом, с которым связаны все остальные элементы и которое является частью программы, ответственной за отображение. 
  Поэтому, по идее, у нас должно быть какое-то глобальное окно, с которым мы свяжем все части нашей игры: меню, карточки, вывод 
  сообщений, кнопки и т.д. по отдельности. Но с другой стороны главным действующим объектом является класс Field и многие другие 
  элементы игры неотрывны от него. Это влечёт за собой необходимость каким-то образом их связывать, так что Field становится ещё одним 
  окном для взаимодействия с пользователем по логике своей работы. Поэтому было принято решение наследовать Field от Window. Это позволило
  создавать глобальное окно (пока без кнопок) и собственно поле.
  
  Возвращаемся к нашим баранам, а именно, кнопкам. После того как игрок нашел две одинаковых картинки, он не может больше взаимодействовать 
  с соответствующими кнопками. Первым нашим (не самым удачным и врядли разумным) решением было простое удаление объектов класса Card. 
  Естественным образом мы столкнулись с рядом поражающих ошибок. Первыми ошибками были: вылет из игры после открытия двух пар карт, не 
  предсказуемое поведение при открытии двух неодинаковых карт (как это вообще случилось) и ошибка, которую мы с легкостью могли 
  считать источником всех зол, - некрасивая дырка посередине поля. Были приняты попытки как-то все это исправить, но страшное серое пятно,
  оставшееся после карты, исправлять было уже сложно. Именно поэтому мы приняли иное решение, которое соответствует канону игры и логично 
  само по себе, - оставлять открытые карточки и (что было пирнято уже под самый конец) отрисовывать поверх первоначального изображения 
  рамки, а сами кнопки делать невидимыми с помощью метода hide().
  
  Тут же возник ещё один вопрос, от которого сильно зависела реализация. В какой момент закрывать неодинаковые карточки? Было придумано 
  три варианта: ждать некоторое время (например, 2 секунды) и закрывать автоматически, ждать клика в произвольное место экрана и после
  него закрывать карточки, ждать клика по любой карточке (к которой не найдена пара, конечно) и после него закрывать старые две и 
  открывать новую. Первый вариант казался привлекательным, но было принято решение от него отказаться, так как пользователю может быть не
  совсем приятно играть в такую игру: через какое именно время карточка должна закрываться, что произойдёт, если пользователь захочет 
  открыть следующую карточку раньше? Второй вариант также был странен с точки зрения процесса игры: пришлось бы делать очень много лишних
  кликов (да и, откровенно говоря, реализация этого метода была не ясна). Поэтому было принято решение остановиться на третьем варианте.
  
  Но не всё, конечно же, так гладко. По описанной логике, программа понимает, что были открыты две одинаковые карточки только после того,
  как пользователь кликнет на третью. А что произойдёт, когда пользователь найдёт последние две? Эта проблема была решена небольшим 
  костылём (который мы так и не придумали как убрать). У класса Field теперь есть счётчик найденных карточек и когда нажимается одна из двух
  последних карточек запускается функция treat_last, которая находит вторую карточку, переворачивает их и завершает игру.
  
  Текущее положение дел таково: реализованы основные части программы, а именно Card, Field, пару вспомогательных классов. На самом деле
  игру уже можно показывать, так как нам осталось отдебажить пару мест и добавить меню. Но это всё не правда и создание класса Mywin, о 
  котором мы говорили ранее, вместе с меню выбора уровней заняло огромное количество времени. Перед его разработкой было принято решение
  навести порядок в иерархии включений и организации кода, а также добавить окно "Play again?", которое после завершения игры предлагало
  пользователю начать игру сначала или выйти. Вот это меню и стала непосредственным поводом для написания myWin... Огромное количество
  времени было потрачено на то, чтобы запихнуть его в Field, но безуспешно. Вообще говоря, сейчас это кажется вполне логичным: какое 
  отношение имеет меню к Field? Но тогда таких мыслей в голове почему-то не возникало. Тем не менее после нескольких часов мучений было
  предпринято решение подойти к делу серьёзно и написать полноценный класс myWin, наследуемый от Window, от которого в свою очередь будет
  наследоваться Field.
  
  В итоге мы получили окно, на котором выводится выбор размера поля, после выбора само поле и кнопка "Quit" и после завершения надпись 
  "Play again?" и две кнопки. На данном этапе большая часть игры была завершена, никаких существенных изменений в структуре не 
  предвиделось, поэтому было принято решение избавиться от таких костылей, как глобальные переменные и магические константы, полностью
  полагаясь на математические расчёты положение поля и передачу параметров по функциям. Это обернулось не самыми приятными, на первый
  взгляд, последствиями. Перестало работать практически всё... После выбора режима игры меню выбора перестало исчезать, и карточки начали
  отрисовываться прямо поверх него. "Play again?" также отрисовывалось на заднем фоне и перестало делать то, что необходимо. Это всё
  заставило нас ещё раз тщательно пересмотреть код на предмет логических ошибок. И они были найдены! Оказывается, меню выбора 
  прикреплялось дважды в совершенно неправильных местах. "Play again?" надо было прикреплять не заранее, а после отрисовки последней пары.
  К тому же это меню пришлось сделать в виде набора кнопок и изображений, так как оно смотрелось просто ужасно на фоне карточек. После
  ещё нескольких часов дебага всё вернулось на круги своя и можно было продолжать избавляться от костылей.
  
  Далее начался процесс поиска любых возможных ошибок в игре. Проверялись различные комбинации карточек, чтобы отловить случаи некорректной
  работы. Были найдены две проблемы. Первая заключалась в том, что при нажатии на карточку, к которой только что была найдена пара, 
  она исчезала, а потом, через несколько ходов, появлялась вновь. Корнем являлось несвоевременное удаление кнопок под карточками. Вторая - 
  в том, что при открытии последней пары одну из карточек можно было перевернуть, и она оставалась перевёрнутой, пока не начнётся новая
  игра. Корнем этой проблемы являлась функция treat_last, в которой не происходило открепления удаления кнопок.
  
  Во время поиска ошибок было найдено также одно улучшение, которое позже мы решили реализовать. Дело в том, что во время игры у 
  пользователя может возникнуть желание начать заново или попробовать другой режим. Сделать это была возможность только выйдя из игры и 
  зайдя в неё заново. Это совершенно не удобно, поэтому было принято решение добавить кнопку "New", которая бы возвращала пользователя на
  экран выбора размера поля.
  
  После последнего улучшения мы посчитали, что дальнейшие нововведения излишни и начали работу над рефакторингом. Нужно было убрать все
  лишние функции, переменные, оптимизировать какие-то алгоритмы, разбить новые классы по файлам и исправить иерархию включений. Также, 
  clang не позволял забыть о warnings, которые тоже было решено максимально исправить.
  
  После этих последних штрихов мы посчитали игру законченной.
  
  