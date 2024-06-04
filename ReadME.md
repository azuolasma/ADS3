# Skolų mokėjimo simuliacija

## Apie užduotį

9. Banko skolų dengimas (ADT: eilė, prioritetinė eilė). Bankas išduoda klientui paskolą, pagal jos sumą ir paskolos laikotarpį sudaromas grąžinimo grafikas (paskolinta suma grąžinama lygiomis dalimis kas 30 dienų). Deja, ne visi klientai sugeba grąžinti paskolą laiku. Atėjus mokėjimo dienai klientas gali turėti tik tiek pinigų, kiek reikia einamajai įmokai pagal grafiką dengti, arba kažkiek daugiau pinigų (tokiu atveju jis dengia ir įsiskolinimus, jei tokių yra), arba kažkiek mažiau pinigų (tokiu atveju auga skolos). Palūkanos skaičiuojamos už visą tam momentui negrąžintą paskolos sumą. Už laiku negrąžintą paskolos dalį imami delspinigiai (delspinigiai neskaičiuojami nuo palūkanų ir delspinigių). Galimos 2 skolų dengimo strategijos: 1) dengiamos seniausios skolos, neatsižvelgiant į jų tipą; 2) dengiama pagal prioritetus: pagrindinė suma, palūkanos, delspinigiai. Įvertinti šių strategijų  ekonominį poveikį klientui. Visi kiti rodikliai, nuo kurių priklauso procesas, įvedami kaip programos parametrai.

### Naudoti ADT:

- Eilė (ieisi9959)
- Prioritetinė eilė (aza9922)

### Funkcijos

- **Skolų grąžinimo strategijos**:
  - **Eilės strategija**: Pirmiausia dengiamos seniausios skolos, neatsižvelgiant į jų tipą.
  - **Prioritetinės eilės strategija**: Prioritetai: Dengiama pagal prioritetus: pagrindinė suma, palūkanos, delspinigiai.
- **Ekonominė analizė**: Programa įvertina šių strategijų poveikį klientui.

### Trūkumai

Neapdorotas atvejis, kai vartotojas neturi pakankamai pinigų sumokėti už mėnesį.

### Naudojimas

loan_manager.exe \<originalAmount> \<interestRate> \<lateInterestRate> \<termMonths>
