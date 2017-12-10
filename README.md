# Домашнее задание по Алгоритмам и структурам данных.
### МГТУ им. Баумана

* [Цель работы](#1)
* [Двоичное дерево поиска](#2)
* [АА-дерево](#3)
* [АВЛ-дерево](#4)
* [Формат данных](#5)
* [План выполнения домашнего задания](#6)

<a name="1"></a>
## Цель работы
Реализовать операции вставки, поиска, удаления, получения минимального и максимального элементов для АА-дерева и АВЛ-дерева.

<a name="2"></a>
## Двоичное дерево поиска
**Двоичное дерево поиска** — это двоичное дерево, для которого выполняются следующие дополнительные условия (свойства дерева поиска):

* Оба поддерева — левое и правое — являются двоичными деревьями поиска.
* У всех узлов левого поддерева произвольного узла X значения ключей данных меньше, нежели значение ключа данных самого узла X.
* У всех узлов правого поддерева произвольного узла X значения ключей данных больше либо равно, нежели значение ключа данных самого узла X.

Очевидно, данные в каждом узле должны обладать ключами, на которых определена операция сравнения меньше.

Как правило, информация, представляющая каждый узел, является записью, а не единственным полем данных. Однако это касается реализации, а не природы двоичного дерева поиска.

**Для целей реализации двоичное дерево поиска можно определить так:**

* Двоичное дерево состоит из узлов (вершин) — записей вида (data, left, right), где data — некоторые данные, привязанные к узлу, left и right — ссылки на узлы, являющиеся детьми данного узла — левый и правый сыновья соответственно. Для оптимизации алгоритмов конкретные реализации предполагают также определения поля parent в каждом узле (кроме корневого) — ссылки на родительский элемент.
* Данные (data) обладают ключом (key), на котором определена операция сравнения «меньше». В конкретных реализациях это может быть пара (key, value) — (ключ и значение), или ссылка на такую пару, или простое определение операции сравнения на необходимой структуре данных или ссылке на неё.
* Для любого узла X выполняются свойства дерева поиска: key[left[X]] < key[X] ≤ key[right[X]], то есть ключи данных родительского узла больше ключей данных левого сына и нестрого меньше ключей данных правого.

#### Базовый интерфейс двоичного дерева поиска состоит из трех операций:

* FIND(K) — поиск узла, в котором хранится пара (key, value) с key = K.
* INSERT(K,V) — добавление в дерево пары (key, value) = (K, V).
* REMOVE(K) — удаление узла, в котором хранится пара (key, value) с key = K.

### Стандартные операции в двоичном дереве поиска, одинаковые для АА-дерева и АВЛ-дереве

#### Search (Поиск)

*T - дерево, K - ключ*

Если дерево пусто, сообщить, что узел не найден, и остановиться.

Иначе сравнить K со значением ключа корневого узла X.
* Если K = X, выдать ссылку на этот узел и остановиться.
* Если K > X, рекурсивно искать ключ K в правом поддереве Т.
* Если K < X, рекурсивно искать ключ K в левом поддереве Т.

#### Min (Минимальное значение)
Так как в бинарном дереве поиска для каждого узла справедливо, что left < right, то соответственно для нахождения наименьшенго элемента  переходим всегда в левую ветку нашего дерева, пока не найдем минимальный элемент.

#### Max (Максимальное значение)
Аналогично с нахождением минимального значения использвуем, что left < right, и соответственно для нахождения наибольшего элемента  переходим всегда в правую ветку нашего дерева, пока не найдем максимальный элемент.

<a name="3"></a>
## АА-дерево

**АA-дерево** — структура данных, представляющая собой сбалансированное двоичное дерево поиска, которое является разновидностью красно-черного дерева с дополнительными ограничениями.

В своих работах *Arne Andersson* приводит простое правило, которому должно удовлетворять AA-дерево:
*к одной вершине можно присоединить другую вершину того же уровня но только одну и только справа.*

Таким образом, введенное понятие уровня вершины не всегда совпадает с реальной высотой вершины (расстояния от земли), но дерево сохраняет балансировку при следовании правилу «одна правая связь на одном уровне». 

```C++
struct node {
    int level; // уровень; 1 у листьев
    T key;  // ключ, данные связанные с вершиной
    node *right; // указатель на правого потомка
    node *left; // указатель на левого потомка
    node *parent; //указатель на родителя
};
```

#### Свойства АА-дерева

* Уровень каждого листа равен 1.
* Уровень каждого левого ребенка ровно на один меньше, чем у его родителя.
* Уровень каждого правого ребенка равен или на один меньше, чем у его родителя.
* Уровень каждого правого внука строго меньше, чем у его прародителя.
* Каждая вершина с уровнем больше 1 имеет двоих детей.

В отличие от красно-черных деревьев, к одной вершине можно присоединить вершину только того же уровня, только одну и только справа (другими словами, красные вершины могут быть добавлены только в качестве правого ребенка).

*На практике в AA-дереве вместо значения цвета для балансировки дерева в вершине хранится информация только о ее уровне.*

В AA-дереве разрешены правые ребра, не идущие подряд, и запрещены все левые горизонтальные ребра. Эти более жесткие ограничения, аналогичные ограничениям на красно-черных деревьях, приводят к более простой реализации балансировки AA-дерева.

#### Балансировка

**Для балансировки АА-дерева нужны следующие две операции:**

**Skew** - устранение левого горизонтального ребра. Делаем правое вращение, чтобы заменить поддерево, содержащее левую горизонтальную связь, на поддерево, содержащее разрешенную правую горизонтальную связь.

**Split** - устранение двух последовательных правых горизонтальных ребер. Делаем левое вращение и увеличиваем уровень, чтобы заменить поддерево, содержащее две или более последовательных правильных горизонтальных связи, на вершину, содержащую два поддерева с меньшим уровнем.

#### Вставка вершины

Как и положено почти любому дереву поиска, вставляем новое значение среди листьев дерева (приписывая ему минимальную высоту). Потом вызываем Split (вернее Split(Skew()) ) для всех узлов по пути от листа до корня. Чем имтируем обычное расщепление 2-3 узлов.

#### Удаление вершины

Как и в большинстве сбалансированных бинарных деревьев, удаление внутренней вершины можно заменить на удаление листа, если заменить внутреннюю вершину на ее ближайшего предшественника. Предшественник находиться в начале последнего левого ребра, после которого идут все правые ребра. В силу свойства всех узлов уровня более чем 1, имеющих двух детей, предшественник будет на уровне 1, что делает их удаление тривиальным. После мы вызываем Split для каждого узла и приводим дерево в подходящий вид.

#### Print

Так как на практике в AA-дереве вместо значения цвета для балансировки дерева в вершине хранится информация только о ее уровне.

Выводим вершины в дереве по уровням, слева направо, начиная с level(1) до level(n).

#### Использование

АА-дерево можно использовать для создания и ведения упорядоченных списков, где нам будет нужно больше искать значения, а не добавлять или удалять их. 

Например для поиска домов на карте, так как новые дома строятся не так часто, а получать их расположение нужно довольно часто, то неплохим выбором бдует использование АА-дерева.

#### Эффективность

Оценка на высоту деревьев соответствует оценке для красно-черного дерева, 2 * log(N), так как AA-дерево сохраняет структуру красно-черного дерева. Следовательно все операции происходят за O(log N), потому что в сбалансированном двоичном дереве поиска почти все операции реализуются за O(h). Скорость работы AA-дерева эквивалентна скорости работы красно-черного дерева, но так как в реализации вместо цвета обычно хранят «уровень» вершины, дополнительные расходы по памяти достигают байта.

<a name="4"></a>
## АВЛ-дерево

АВЛ-дерево — это прежде всего двоичное дерево поиска, ключи которого удовлетворяют стандартному свойству: ключ любого узла дерева не меньше любого ключа в левом поддереве данного узла и не больше любого ключа в правом поддереве этого узла. Это значит, что для поиска нужного ключа в АВЛ-дереве можно использовать стандартный алгоритм. Для простоты дальнейшего изложения будем считать, что все ключи в дереве целочисленны и не повторяются.

```c++
struct node {
    T data; //ключ, данные связанные с вершиной
    struct node *left; // указатель на левого потомка
    struct node *right; // указатель на правого потомка
};
```

Особенностью АВЛ-дерева является то, что оно является сбалансированным в следующем смысле: для любого узла дерева высота его правого поддерева отличается от высоты левого поддерева не более чем на единицу.

#### Баланировка 

Относительно АВЛ-дерева балансировкой вершины называется операция, которая в случае разницы высот левого и правого поддеревьев = 2, изменяет связи предок-потомок в поддереве данной вершины так, что разница становится <= 1, иначе ничего не меняет. Указанный результат получается вращениями поддерева данной вершины.

**Используются 4 типа вращений:**

* *Малое левое вращение* - данное вращение используется тогда, когда высота b-поддерева — высота L(находиться в a-поддереве) = 2  и высота С(находиться в b-поддереве) <= высота R(находиться в b-поддереве).
* *Большое левое вращение* - Данное вращение используется тогда, когда высота b-поддерева — высота L(находиться в a-поддереве) = 2 и высота c-поддерева(находиться в b-поддереве) > высота R(находиться в b-поддереве).
* *Малое правое вращение* - Данное вращение используется тогда, когда высота b-поддерева — высота R(находиться в a-поддереве) = 2 и высота С(находиться в b-поддереве) <= высота L(находиться в b-поддереве).
* *Большое правое вращение* Данное вращение используется тогда, когда высота b-поддерева — высота R(находиться в a-поддереве) = 2 и высота c-поддерева(находиться в b-поддереве) > высота L(находиться в b-поддереве).

В каждом случае достаточно просто доказать то, что операция приводит к нужному результату и что полная высота уменьшается не более чем на 1 и не может увеличиться. Также можно заметить, что большое левое вращение это композиция правого малого вращения и левого малого вращения. Из-за условия балансированности высота дерева О(log(N)), где N- количество вершин, поэтому добавление элемента требует O(log(N)) операций.

#### Вставка вершины

Вставка нового ключа в АВЛ-дерево выполняется, по большому счету, так же, как это делается в простых деревьях поиска: спускаемся вниз по дереву, выбирая правое или левое направление движения в зависимости от результата сравнения ключа в текущем узле и вставляемого ключа. Единственное отличие заключается в том, что при возвращении из рекурсии (т.е. после того, как ключ вставлен либо в правое, либо в левое поддерево, и это дерево сбалансировано) выполняется балансировка текущего узла. Строго доказывается, что возникающий при такой вставке дисбаланс в любом узле по пути движения не превышает двух, а значит применение вышеописанной функции балансировки является корректным.

#### Удаление вершины

Для простоты опишем рекурсивный алгоритм удаления. Если вершина — лист, то удалим её и вызовем балансировку всех её предков в порядке от родителя к корню. Иначе найдём самую близкую по значению вершину в поддереве наибольшей высоты (правом или левом) и переместим её на место удаляемой вершины, при этом вызвав процедуру её удаления.

Докажем, что данный алгоритм сохраняет балансировку. Для этого докажем по индукции по высоте дерева, что после удаления некоторой вершины из дерева и последующей балансировки высота дерева уменьшается не более, чем на 1. База индукции: Для листа очевидно верно. Шаг индукции: Либо условие балансированности в корне (после удаления корень может изменится) не нарушилось, тогда высота данного дерева не изменилась, либо уменьшилось строго меньшее из поддеревьев => высота до балансировки не изменилась => после уменьшится не более чем на 1.

Очевидно, что в результате указанных действий процедура удаления вызывается не более 3 раз, так как у вершины, удаляемой по второму вызову, нет одного из поддеревьев. Но поиск ближайшего каждый раз требует O(N) операций. Становится очевидной возможность оптимизации: поиск ближайшей вершины может быть выполнен по краю поддерева, что сокращает сложность до O(log(N)).

#### Эффективность

Из формулы, приведённой выше, высота АВЛ-дерева никогда не превысит высоту идеально сбалансированного дерева более, чем на 45%. Для больших n имеет место оценка 1.04 log2n. Таким образом, выполнение основных операций требует порядка log2n сравнений. Экспериментально выяснено, что одна балансировка приходится на каждые 2 включения и на каждые 5 исключений.

#### Print

**Выводиться дерево будет по методу PreOrder traversal, так как этот метод наиболее точно показывает, что не нарушается главное свойство АВЛ-дерева: "для любого узла дерева высота его правого поддерева отличается от высоты левого поддерева не более чем на единицу"** 

Имеется у нас такое дерево.
                        
                        5
              3                    11
          2      4             8       15
                            6

* *PreOrder traversal. Ввод: 5  3  2  4  11  8  6  15 (обойти всё дерево, следуя порядку (вершина, левое поддерево, правое поддерево). Элементы, как в дереве) *

#### Использование 

АВЛ-дерево можно использовать, для сортировки массива из N элементов, так как можно его просто добавить в дерево – N*log(N) а потом обойти слева направо – N т.е. суммарное время N*log(N) – и мы сделали очередной очень быстрый метод сортировки массива.

Поиск, вставка, удаление, минимальные и максимальные операции выполняются в O(logN). 

Деревья AVL полезны в тех случаях, когда разрабатывается некоторая баз данных, где вставки и удаления происходят не часто, но приходится часто искать данные, присутствующие там.

Например база данных для поездов в железнодорожной системе. Так как поезда выходят не так часто и структура структура остается пригодной продолжительный срок. Реализация АВЛ-дерева в этом случае будет лучше, чем любое другое дерево для поиска. 

<a name="5"></a>
## Формат данных

### Формат входных данных

Входной файл содержит последовательность команд, т.е. представляет набор строк вида

**command [key] [data]**

где *command* — *add*, *delete*, *search*, *min*, *max*, *print* или *спец. команда*;

key — ключ, целое число; 

data — данные, целое число. 

**Примеры:**

*add 10 20* 

*search 15* 

*print*

*min*

### Формат выходных данных

На выходе программы получаем оценку корректности всех алгоритмов, реальную оценку времени, затраченного на выполнение команды и объем использованной при этом памяти.

В выходной файл выводятся результаты исполнения программы. 
Команда *print* должна отражать внутреннее строение структуры данных

Команда *pearch* выводит "Yes" или "No", в зависимости от того, найдено было значение или нет.

Команда *add* добавляет значение в дерево (Ничего не выводит).

Команда *delete* удаляетя число (Ничего не выводит).

Команда *min* выводит минимальное число в дереве.

Команда *max* выводит максимальное число в дереве.

Результатом выполнения работы будет исходная таблица, которая содержит реальную оценку времени исполеннияя команды.

### Тесты

Создаются тесты, для одинаковых операций в АА-дереве и АВЛ-дереве. Для каждого дерева берутся одни и те же данные. Засекается время начала исполнения операции и ее конца, после чего берем разницу. Проделыываем предыдущее действее множество раз для разных операций, затем прощитываем погрешность и получаем наиболее точнее время исполнения операции. Заносим в итоговую таблицу время для каждого дерево. В итоге, получаем таблицу, в которой описано время исполенения операций для каждого дерева.

####Выполняется два вида тестов
**Корректность работы структуры**

*Бралось среднее время с 15 попыток. (В миллисекундах)*

На вход программе подается три файла. 

1) Входной файл.
2) Выходной файл с результатами исполнения программы.
3) Файл с правильными ответами.

Три теста, в соответсвии с сценариями использования и не только:

1) Мало добавлений и удалений, много поисков (AVL - 2.433, AA - 2.695)
2) Много добавлений и удалений (AVL - 2.34, AA - 2.613)
3) Посики минимальных и максимальных значений (AVL - 2.207, AA - 2.365)

Результыты тестов проверялись на с заготовленным файлом с правильными ответами.

**Время работы**

Время работы рачитываем тестом с 1000 добавлениями.

AVL - 9.971

AA - 12.635


<a name="6"></a>
## План выполнения домашнего задания 

1. Реализовать АА-дерево.
2. Реализовать АВЛ-дерево.
3. Написать тесты стандартным операциям в двоичном дереве поиска. (Search, Min, Max)
4. Написать тесты к основным методам АА-дерева. (Вставка, удаление, вывод)
5. Написать тесты к основным методам АВЛ-дерева. (Вставка, удаление, вывод)
6. Оценить достаточно ли данных тестов для сравнения структур.
7. Доработать тесты при необходимости и поправить последние баги.
8. Повторить пункты 6 и 7. 
9. Проанализировать полученные результаты и написать вывод. 
10. Оформить отчет.
