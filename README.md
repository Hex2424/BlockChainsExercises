# **BlockChainsExercises (v0.1)** #

**EHash hashavimo funkcija:
* **Feature: (256 bitai yra tik nustatyta, galima nustatyti betkokį ilgį)**

# Naudojimas:
```sh
    HashAlgorithm <text_to_hash> / HashAlgorithm -f <filepath>
```
* Palaikomas ranka ivedimas;
* Palaikomas skaitymas is failo;

# Testai:

## 1. Sukuriami testiniai įvedimo failai /* gaunami hashai ##

## **Mazo dydzio Test:** ##
* **Failas turintis simbolį "a"**
```txt
c7e147d8ba83ace574bd4669e938aa755844dfa869e457c780c849312fd22051
```
* **Failas turintis simbolį "b"**
```txt
da70f0b154bde32552f7a3a023ed268aa10aee89530b8698f9b94f675d97738b
```
## **Atsitiktiniu Test:** ##

* **Failas turintis 32k atsitiktiniu simboliu**
```txt
acd5d5bbbd54fa7ec455c25647eb4d7676d36d146801c9a923ba01694e02bd5f
```

* **Failas turintis 3k atsitiktiniu simboliu**
```txt
6e241e9623394c269cd3ce88f80fedab536ad9282f6e73e87a1340ddc531c98d
```
## **Avalanche Test:** ##

* **Failas turintis 30k atsitiktiniu simboliu (nekeistas)**
```txt
ee196cc0b246738f7f9c8f4b57a9f49ff7a23361347f70c0b2f05676c55c7001
```

* **Failas toks pat turintis 30k atsitiktiniu simboliu (pakeista viduryje raide b -> a)**
```txt
a671a6788572c16e58fbb5b4dd42d0c7493bde7fe053fed85323df2417d6bea7
```
## **Null character hashing test** ##

* **Failas kuris yra tuscias**
```txt
ca70a0f94ee3cbe5381b7d081dcff1628bcbe8a9d9fe2a2a27230120ef10a85c
```

## 2. Matoma jog outputai yra tokio pat dydzio - 64 baitai##

## 3. Efektyvumo analize: ##

 - Debug
    ![Alt text](/greicio_testas.png?raw=true "Optional Title")
    lines -> time(seconds)
    * 1 -> 0.000030 (s)
    * 2 -> 0.000035 (s)
    * 4 -> 0.000034 (s)
    * 8 -> 0.000037 (s)
    * 16 -> 0.000063 (s)
    * 32 -> 0.000068 (s)
    * 64 -> 0.000109 (s)
    * 128 -> 0.000229 (s)
    * 256 -> 0.000514 (s)
    * 512 -> 0.001228 (s)

**- 10 millions file hashed in debug mode: 0.285256 s**
- Release
    * 1 -> 0.000018 (s)
    * 2 -> 0.000029 (s)
    * 4 -> 0.000047 (s)
    * 8 -> 0.000019 (s)
    * 16 -> 0.000028 (s)
    * 32 -> 0.000029 (s)
    * 64 -> 0.000041 (s)
    * 128 -> 0.000081 (s)
    * 256 -> 0.000157 (s)
    * 512 -> 0.000357 (s)

**- 10 millions file hashed in release mode: 0.119841 s**


## 4 - 5. Collisionu testai: ##

* Testavimo failas su 500k lietuvisku slaptozodziu - Ne karto nesikartojo hashas
* Testavimo failas su poromis skirtingo ilgio 200k - Ne karto nesikartojo

```txt
Kadangi hashas supportina betkokio bitų ilgio output, testavau 500k collisionų failą su 64bit output hashu (16 baitų ilgio), nebuvo nė karto collisiono 500k dydžio faile.
```

## 6. Sutapimu testai: ##
```txt
Testuota su 200k poru failu
```
* **Baitų** lygio sutapimai : **393883** kartų arba **6.1544%**
* **Bitų** lygio sutapimai  : **27878077** kartų arba **54.4494%**

## 7. Apibendrinimas: ##

- Privalumai

    * Hashas gali but nustatomas betkokio ilgio bitų (ne tik 256)
    * Nenustatyta praktikoje collisionu
    * Pakankamai didelis efektyvumas (O(n) sudėtingumas)
    * Kuo didesnis failas, tuo geriau sumaišoma

- Trūkumai
    * Gali atsirast spragų hasho pradžioje, ji yra mažiau išmaišoma kai inputas mažas.
    * Bitų lygmens sutapimas gan aukštas. (4% didesnis nei norma)
