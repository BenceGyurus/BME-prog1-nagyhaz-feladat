A program morze kódot tud **enkódolni** és **dekódolni**, azaz szöveget tud morze kóddá kódolni és a morze kódot szöveggé visszakódolni. **Enkódolás esetén az angol ábc betűi, számok 0-tól 9-ig valamint néhány speciális karakter**, mint `!` `"` `@` **használható**, de nem tartalmazhat például ékezetes karaktereket vagy `\n`-t. Dekódoláskor **csak a morze karakterkészlete**, azaz `.` és  `-` **használható**, az új karaktert space-el kell elkülöníteni illetve a space karaktert a `/` karakter helyettesíti. Pl.: `.... . .-.. .-.. --- / .-- --- .-. .-.. -.. --.--` Sem a dekódolás, sem a kódolás során nem tesz különbséget a kis és nagybetűk között. A karakterkészlet szerkeszthető a `./szotar.txt`-ben.
A program helytelen bemenetet kap:
- Ha nem a megadott funkciók közül választ a felhasználó
- Ha nem a funkciónak megfelelő karaktereket kapja
- Ha parancssorból indítva több vagy kevesebb paramétert kap az elvártnál
## Fordítás:
```shell
gcc -Wall -Werror *.c -o morse
```
## A program futtatása:
A program futtatására **2 lehetőség** van:
- parancssorból egysorban
- parancssorból menüvel
## Parancssorból egysorban:
Ebben az esetben a program futása alatt a futtatás előtt megadott paraméterek alapján fog lefutni. Futtatáshoz be kell írni a program nevét majd üres hely után következik a funkció kiválasztása, `e`-vel lehet az enkódoló funkciót kiválasztani valamint `d` betűvel a dekódoló funkciót. A következő paraméter üres helyet követően idézőjelek között az enkódoloandó vagy dekódolandó karakterlánc.

| funckció | paraméter | leírás                      |
| -------- | --------- | --------------------------- |
| enkód    | -e        | szöveget kódol morze kóddá  |
| dekód    | -d        | moze kódot dekódol szöveggé |

### Példa

#### Dekódolás
```shell
./morse -d ".... . .-.. .-.. --- / .-- --- .-. .-.. -.. --.--"
```

#### kimenet:
```
HELLO WORLD!
```

#### Enkódolás
```shell
./morse -e "Hello world!"
```
#### kiment:
```
.... . .-.. .-.. --- / .-- --- .-. .-.. -.. --.--
```
## Parancssorból menüvel:
Ilyenkor a programot paraméterek nélkül kell elindítani. Ebben az esetben a program menüvezérelt lesz. Ha program sikeresen előkészítette a kódolást és dekódolást akkor a parancssorban `Enkódolni (e) vagy dekódolni (d) szeretne? Kilépés: /e [e/d]:` kérdést kell látni. Ekkor a felhasználó választhat a dekódolás, az enkódolás és a kilépés között. Amennyiben kiválasztotta a funkciót (enkódolás esetén e dekódolás esetén d betűt ír be, majd enter-t üt) be kell írnia a kódolandó/dekódolandó szöveget, a szöveg beírását követően, ha helyes volt a bemenet (csak a megengedett karaktereket tartalmazza) a beírt szövegnek megfelelő morze kód vagy a beírt morzekódnak megfelelő szöveg jelenik meg, majd a felhasználó visszakerül a menübe. Amennyiben tévesen választotta ez a menüt egy enter-t ütve szintén visszakerül a menübe. A menüből a `/e`-t begépelve majd enter-t ütve lehet kilépni.
#### Helyes bemenet:
```
Enkódolni (e) vagy dekódolni (d) szeretne? Kilépés: /e [e/d]: e

Írja be a kódolandó szöveget >>Hello world!
.... . .-.. .-.. --- / .-- --- .-. .-.. -.. --.-- 
Enkódolni (e) vagy dekódolni (d) szeretne? Kilépés: /e [e/d]: d

Írja be a dekódolandó morze kódot >>.... . .-.. .-.. --- / .-- --- .-. .-.. -.. --.--
HELLO WORLD!
```
#### Hibás bemenet a menüben:
```
Enkódolni (e) vagy dekódolni (d) szeretne? Kilépés: /e [e/d]: s

Kérem válasszon funkciót!
```
#### Hibás bemenet enkódolás/dekódolás közben:
```
Enkódolni (e) vagy dekódolni (d) szeretne? Kilépés: /e [e/d]: e

Írja be a kódolandó szöveget >>Hello világ
.... . .-.. .-.. --- / ...- .. .-.. 
Hibatörtént! Ismeretlen karakter: �

Enkódolni (e) vagy dekódolni (d) szeretne? Kilépés: /e [e/d]: d

Írja be a dekódolandó morze kódot >>Hello világ
A dekódolandó szöveg nem tartalmazhat a szóköztől, '.'-tól '-'-től és '/'-től különböző karaktert.
```
