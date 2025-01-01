# Qt-Binairo-game

**NOTE!**

Not everything in this code is written by me. This was a school project where we were given this template that we had to use to build out binairo game off of.
Basically the gameboard header andd source files have **NOT** been created by me. The mainwindow header and source files have been created by me which contains all the graphical user interface (GUI) stuff. Due to this I will only publish the mainWIndow code and a video of running the code. 

In this project we were tasked to create an gui for a binairo game. We had already during the course created the basic console versino that is the gameboard here, but now we were given this template to use
although we could have used that. So now our job was to create Gui the user could use to play the binairo. Other requirements were to give the user the choise to either input custom starting board or to use random board, 
 a reset button and a timer. We also could desing features for extra point which I did.  I added a graphical way to alter the gameboard size, pictures for the game pieces (simple dots), a score counter, and I also added feature where the background changes color when the user wins the game.
 From this Task I received full points 100/100


 This was the first prroject where I created a grahical user inteface in c++. This project taught me alot about creating Gui's and also about QT creators desing tools and how to implement them.

The folowing is a instruction manual I wrote for this code, where I explained how to use the code and how I planed and developed this code. It is only writen in finnish: 

Henri Laitinen, 150500492 Binairo Gui tehtävän dokumentaatio

Pelaamisohjeet:
Ohjelman alkaessa ruudun vasemmassa laidassa on pelilaudan koko valitsin sekä vaihtoehdot joko satunaiselle pelilaudan täyttämiselle tai itse syöttämis vaihtoehto. Kun valitsee toisen näistä aukeaa alapuolelle joko LIneEdit laatikko johon voi syöttä oman inputin tai spinBox johon voi syöttää random siemenen 0-50. Jos valitsee input syötteen kirjoita laatikkoon haluamasi pelilauta rivi kerrallaan allekkain, huomioi pelilaudan koko jonka olet valinnut yläpuolella. Käytä tyhjän pelinappulan merkkinä viivaa (-) ja muita nappuloita numeroin 0 ja 1
esimerkki 3x3 pelilaudan täytöstä:  1-0
				    0--
				    --1
Jos syötteesi on väärän kokoinen tai sisältää vääriä merkkejä, saat ilmoituksen, täytä syöte uudelleen.
Random simementä valitessa saat myös ilmoituksen huonosta siemenestä, valitse tällöin uusi siemen. Jos haluat sittenkin toisen täyttötavan paina undo nappia jolloin palataan alkutilanteeseen. 

Jos syöte on hyvä aukeaa info tekstin kohdalle pelilauta. Pelilaudan oikealla puolella on valinta napit 0 ja 1, joista valkoinen pallo kuvastaa nollaa ja musta pallo kuvastaa ykköstä. Pelatakseen peliä valitse ensin oikealta minkä nappulan haluat laittaa pelilaudalle. Valittua nappulaa indikoi sen alapuolella oleva punainen nuoli. Seuraavaksi paina pelilaudalta tyhjää nappulaa jonka paikalle haluat sijoittaa valitsemasi nappulan. Jos valinta on sopiva päivittyy pelilauta sen mukaisesti, jos valinta ei sovi siiheen paikkaan, saat virheilmoituksen ja voit valita toisen nappulan sijoittaakseen. 

Jos haluat missä vaiheessa vain pelia aloittaa uudestaan pelin, paina oikeassa ylänurkassa sijaitsevaa reset nappia, jos haluat lopettaa pelin paina close nappia, joka sulkee ja lopettaa sovelluksen pyörimisen. 


Ohjelman suunnitelu ja toteutus: 
Lähdin toteuttamaan peliä samassa järjestyksessä missä pelin ominaisuudet ilmaantuvat normaalin pelikerran aikana. Lähdin siis liikeelle alkunäytön rakentamisessa. Rakensin aloitusnäytön täysin qtDesinger:ssa. Info laatikon alkuperäinen tarkoitus oli piilottaa mahdollinen pelilauta, mutta päädyin myöhemmin synnyttämään uudet pelinappulat joka pelikerralla uudestaan. Tämä helpottaa pelilaudan hallitsemista ja vältytään turhilta ->show(), ->hide() komennoilta joita on nyt jo koodissa melko paljon. alkunäytöllä random ja input napit ovat yhdistetty valintaan tarkoitettuu lineEdit laatikkoon ja sitä indikoivaan labeliin ja random seed spinBoxiin ja sitä indikoivaan labeliin, nämä tuodaan näkyviin nappia painamalla. Undo nappi puolestaan piilottaa nämä napit ja tuo uudelleen esille random ja input napit. Kun painetaan create gameboard nappia, otetaan input laatikosta inputti tai random siemen spinBoxista siemen ja kutsutaan gameboard.cpp:n peliluadan luonti funktioita. Jos pelilauta luodaan onnistuneesti aloitetaan peli kutsumalla startGame() funktio. Pelilauta on tallennettu mainWindow luokassa GameBoard olioon board.

Ensimäinen toteutettu lisäominaisuus on pelilaudan koon muuttaminen käyttöiättömästä. Pelilaudan kokoa voi vaihtaa ennen pelin aloittamista spinBox:ista ruudun vasemmasta laidasta. Tämän spinBoxin arvon muuttaminen johtaa siihen, että MainWindow luokassa uusi luku tallennetaan numberOfPieces muuttujaan, ja koko pelilaudan koko tallennetaan sizeMain muuttujaan kertomalla numberOfPieces kahdella. Gameboard luokassa kutsutaan funktiota change_size funktiota joka muttaa sen luokan NUMBER_OF_PIECES muuttajan arvoa ja samalla muutetaan myös SIZE muuttujan arvo uudeksi. Täten pelin ruutu muuttuu ja samalla tarkistus muuttuu oikeaksi, eli ruudukossa saa olla aina maksimissaan numberOfPieces verran samaa merkkiä per rivi. 

startGame funktio piiloittaa aloitusnäytön objektit, tuodaan esiin ja käynnistetään ajastin sekä kutsutaan initGameboard ja initChoises funktioita jotka luovat käyttöliittymään painonapeista koostuvan pelilaudan ja valinta napit. Pelinappuloita luodaan for loopilla niin paljon kuin käyttäjän valitsema koko vaatii. Jokaisen pelinappulan pointer tallennetaan myös gameboardButtons vektoriin. Jokaisen pelinappulan koordinaatit on myös tallennettu objektin nimeen. Samaan aikaan kun tein näitä funktioita tein myös toisen lisäominaisuuden eli käytin eri pelinappuloiden ilmaisemiseen kuvia. Kuvat ovat itse piirretty paintilla. Kuvat asetetaan pelinappuloihin Ikoneiksi pixMapin avulla. Kuvat asetetaan pelinappuloihin samalla kun nappuloita luodaan. Jotta nappulat tulevat näytölle oikein, on keskelle näyttöä laitettu gridLayout. valinta nappulat ovat luotu samallalailla mutta vain initChoises funktiossa. 

Kun jotain valinta nappia tai pelilaudan nappia painetaan, käytään nappeja tallentavat vektorit läpi ja katsotaan mikä napeita on signaalin lähettäjä. Jos nappi on signaalin lähettäjä, lisätään uusi pelinappula pelilaudalle gameboard.cpp:n komennolla add_symbol. Jos lisäys onnistuu päivittyy pelinappulan kuva ja pelilauta board. Jos lisääminen ei onnistu, tulee näytölle virheilmoitus ja pelaajan tulee valita uusi nappula/paikka. 

Jokaisen sijoitetun nappulan jälkeen tarkistetaan onko peli loppu gameboard.is_game_over() funktiolla. jos peli on loppu tulosetetaan näytölle voitto teksti jossa ilmoitetaan peliin kulunut aika ja saadut psitete. Tämän jälkeen pelaaja voi aloittaa uuden pelin painamalla reset nappulaa tai lopettaa pelaamisen painamalla close nappulaa.

Jos pelaaja painaa reset nappulaa, kutsutaan tällöin reserButtonCliked() funktiota. Tämä funktio poistaa kaikki luodut pelinappulat ja valinta nappulat sekä tyhjentää vektorit joissa on säilötty näihin nappeihin osottavat pointerit. Samalla myös kutsutaan gameboard.cpp:hen luotua reset_board funktiota joka tyhjentää myös gameboard funktiossa säilötyn pelilaudan. Samalla tuodaan taas näkyviin kaikkialkunäytön objektiti show() komennolla ja piilotetaan pelin aikaiset objektit ja pysäytetään kello stopTimer funktiolla. Reset nappi on pois käytöstä ennen ensimäisen pelilaudan luomista, sillä sen painaminen ennen tätä johtaa ohjelman kaatumiseen. 

close nappi sulkee käyttöliittymän. 

Kolmantena lisäominaisuutena ohjelmaan on toteutettu pisteen lasku. Käyttäjä saa yhden pisteen jokaisesta asetetusta pelinappulasta. Aina kun nappulan asetus on onnistunut kutsutaan addPoint funktioi joka lisää points muutujaan pisteen ja päivittää sitä esittävän labelin pointCounter. Pelin lopussa pisteet kerrotaan ajan kanssa. 

Neljäntenä lisäominaisuutena lisätty taustavärin muuttaminen pelin loppuessa. Tämä toteutetaan kutsumalla käyttöliittymän (this) valmista funktioita setStyleSheet() funtioissa gameWon ja asettamalla tausta väri vaalean siniseksi. Reset nappia painamalla asetetaan taustaväri takaisin "normaaaliksi"



 
