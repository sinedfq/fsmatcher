# FSMATCHER - курсовая работа по программированию

Курсовая работа студента группы ИВ-121 Хухарев Денис <br>
Тема курсовой работы: "Поиск посдстроки в строке при помощи конечного автомата"<br>
Предмет: Программирование, 1 к. 1 c.

## О конечном автомате

Конечный автомат (или попросту FSM — Finite-state machine) это модель вычислений, основанная на гипотетической машине состояний. В один момент времени только одно состояние может быть активным. Следовательно, для выполнения каких-либо действий машина должна менять свое состояние. <br> <br>

Конечные автоматы обычно используются для организации и представления потока выполнения чего-либо. Это особенно полезно при реализации ИИ в играх. Например, для написания «мозга» врага: каждое состояние представляет собой какое-то действие (напасть, уклониться и т. д.). <br><br>

Конечный автомат можно представить в виде графа, вершины которого являются состояниями, а ребра — переходы между ними. Каждое ребро имеет метку, информирующую о том, когда должен произойти переход. Например, на изображении выше видно, что автомат сменит состояние «wander» на состояние «attack» при условии, что игрок находится рядом. <br><br>

## Планирование состояний и их переходов

Реализация конечного автомата начинается с выявления его состояний и переходов между ними. Представьте себе конечный автомат, описывающий действия муравья, несущего листья в муравейник: <br><br>
Отправной точкой является состояние «find leaf», которое остается активным до тех пор, пока муравей не найдет лист. Когда это произойдет, то состояние сменится на «go home». Это же состояние останется активным, пока наш муравей не доберется до муравейника. После этого состояние вновь меняется на «find leaf».<br><br>

Если состояние «find leaf» активно, но курсор мыши находится рядом с муравьем, то состояние меняется на «run away». Как только муравей будет в достаточно безопасном расстоянии от курсора мыши, состояние вновь сменится на «find leaf».<br><br>

##  Поиск подстрок с помощью конечных автоматов

Поиск подстроки с помощью конечного автомата Мура весьма эффективен: каждый символ поступает на вход автомата только единожды, так что общее время работы (n). Однако алгоритм требует предварительной подготовки – построения конечного автомата. Время, затраченное на построение автомата, может быть весьма значительным, особенно если велик алфавит . <br><br>

Дадим формальное определение конечного автомата. Конечный автомат представляет собой пятерку объектов M = (, Q, q0, F, ), где:

-  – конечный входной алфавит;

- Q – конечное множество состояний;

 - q0 – начальное состояние автомата;

- F – подмножество выходных (допускающих) состояний, F  Q;

 -  – функция переходов.

Первоначально автомат находится в начальном состоянии q0; затем он по очереди читает символы входной строки. Находясь в состоянии qi и читая символ , автомат переходит в состояние qj. В какое именно состояние перейдет автомат под действием прочитанного символа, определяется функцией переходов . <br>

Состояния qp,..qp+z, входящие в подмножество выходных состояний F, соответствуют окончанию распознавания образцов P1…PZ. Когда автомат находится в выходном состоянии qp+i, это означает, что найдено вхождение образца Рi в текст со сдвигом s = k–mi, где k – номер последнего считанного символа входной строки, mi – длина i-го образца.

Конечный автомат для распознавания единственного образца Р [1..m], имеет m+1 состояние Q = {0,1,…m}. Состояние с номером 0 является начальным, с номером m – выходным (допускающим).

Прежде чем перейти к созданию функции переходов, необходимо дать определение суффикс-функции.

Суффикс-функция (х) ставит в соответствие строке х длину максимального суффикса х, являющегося префиксом образца Р. Суффикс-функция принимает значения целых чисел от 0 до m. Например, для образца P = ab ()=0, (a)=1, (cda)=1, (ccdab)=2, (ccdabc)=0.

Функция переходов (qi,) показывает номер состояния, в которое перейдет конечный автомат из состояния qi под действием символа . Она равна 

<div align = "center"> (qi, ) = (Pi ) </div>

<br>
здесь Pi  обозначает конкатенацию префикса Р длины i с символом .

Построить конечный автомат для поиска образца P = ababaca.

Входной алфавит конечного автомата ограничен тремя символами: ={a,b,c}. Длина образца |P|=7, поэтому конечный автомат будет иметь восемь состояний с номерами от 0 до 7. Значения суффикс-функции 

![Model](https://studfile.net/html/2706/71/html_EyshsRlYwX.ociy/img-ZKN7pk.png)

Рассмотрим, как вычисляется суффикс-функция на примере 3-й строки таблицы. Префикс образца Р длиной 3 равен Р3 =aba. Для каждого символа из алфавита ={a,b,c} получаем конкатенацию подстроки Р3 с этим символом:

<div align = "center">
с символом a: Р3а =abaa <br>
с символом b: Р3b =abab <br>
с символом c: Р3c =abac <br>
</div>
<br>
Затем, для каждой конкатенации P3 (здесь  обозначает символ из алфавита) ищем суффикс P3 максимальной длины, одновременно являющийся префиксом образца Р.  Его длина и есть значение суффикс-функции (P3 ).

У строки Р3а =abaa и образца P = ababaca общая часть – это один символ a (здесь и далее общие части подчеркнуты), следовательно, значение суффикс-функции (Р3а)=1.

У строки Р3b =abab есть два суффикса, являющиеся префиксами образца Р. Это ab (Р3b = abab, P = ababaca) и abab (Р3b = abab, P = ababaca). Выбираем суффикс максимальной длины (4), значение суффикс-функции (Р3b)=4.

У строки Р3с = abaс нет суффиксов, совпадающих с префиксами образца P, поэтому суффикс-функция (Р3с)=0.

Диаграмма переходов конечного автомата, построенная по таблице, показана на рис.1. Выходное состояние автомата 7 обведено двойным кружком. На диаграмме не показаны стрелки, ведущие в 0-е состояние. Если из состояния i не выходит стрелки, помеченной символом , то подразумевается, что (i,) = 0.

## Ссылки на оригиналы статей

- Постановка задачи поиска подстрок : https://studfile.net/preview/7416350/page:3/
- Конечный автомат: теория и реализация : https://tproger.ru/translations/finite-state-machines-theory-and-implementation
