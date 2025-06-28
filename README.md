# Kayıp Top – OpenGL Kısa Animasyon Projesi 🎮🌲

Bu proje, bir çocuğun gece vakti ormanda kaybolan topunu aradığı kısa animasyon hikayesini modern OpenGL kullanarak görselleştirir. Kullanıcı, karar verme anlarında hikayeye yön verirken sahne, aydınlatma ve kamera geçişleriyle sinematik bir deneyim sunar. Kullanıcı toplam 5 adet kamera açısıyla animasyonu 5 farklı şekilde deneyimleyebilir. Sahnenin ana karakteri çocuğa yol göstererek ne yapması gerektiğini söyleyebilir. Kullanıcı ne yapması gerektiğini ekranın sol altındaki bildirim satırından görüntüleyebilir. Ana karakterin çıkardığı sesler ile animasyonun içine girer.

---

## 🎬 Hikaye

Bir çocuk gece ormanda oynarken topunu kaybeder. Yalnız gece ormanda yürümekten korktuğu kadar hiçbir şeyden korkmaz. Sabahı beklemeyi düşünse de en sevdiği kırmızı topun korkutucu seslerle bilinen ormanda bir gece dayanmasını istemez. Ne yapacağını bilemeyen çocuk el fenerini eline alır ve ormanda topunu aramaya koyulur.El fenerini bulup yaktığında karanlık ormanın içine doğru ilerlemeye başlar. Önünde iki yol çıkar: bir patika ve ormanın karanlık kısmı. Seçime göre hikaye ilerler: yanlış yola giderse topu bulamaz, doğru yolu seçerse korkutucu bir sesle karşılaşır. Devam ederse topuna kavuşur devam etmez ise çocuk  geri döner cesaretini toplar ve topuna ulaşır. Bütün bunlar en sevdiği topu içindir ancak çocuğun bu topu bu kadar sevmesinin nedeni izleyicilerine kalmış.....

---

## 🛠️ Özellikler

- 🌲 **Gerçekçi Orman Ortamı**: Ağaçlar, orman zemin dokusu, yollar.
- 🔦 **El Feneri Işığı**: Spotlight efekti, sadece aktifken çevreyi aydınlatır.
- 🎧 **Ses Efektleri**: Fener açma sesi, korku ve sevinç sesleri.
- 🎥 **Çoklu Kamera Modları**:
  - Birinci şahıs (FPS)
  - Üçüncü şahıs (TP)
  - Yukarıdan bakış (Overhead)
  - Serbest kamera (Free cam – WASD + fare)
  - Sabit uzaktan kamera
- 🧠 **Hikaye Seçimi**: Kullanıcı tuşlarla yön verir (1 → Patika, 2 → Orman). Kullanıcı bilgilendirme satırıyla bilgilendirilir.
- 🧍 **Karakter Animasyonu**: Yürüme animasyonu ve otomatik hareketler.

---

## 🧰 Kullanılan Teknolojiler ve Kütüphaneler

- **OpenGL 3.3 Core** – Grafik render
- **GLFW** – Pencere, giriş kontrolü
- **GLAD** – OpenGL fonksiyon yükleyici
- **GLM** – Matris ve vektör hesaplamaları
- **stb_image / stb_easy_font** – Texture ve metin çizimi
- **WinMM** – Windows ses fonksiyonu ile ses çalma (PlaySound)

---

## 🗺️ Sahne ve Mimari

### 🎞️ Yapılar:
- `Scene` sınıfı: Ağaçlar, zemin, patika ve top objelerini çizer.
- `Character` sınıfı: Ana karakterin pozisyonu, yönü, animasyonu.

### 🔦 Shader Yapısı:
- **Vertex Shader**: Model, view, projection matrisleri ile nesneleri dönüştürür.
- **Fragment Shader**: Ambient + spotlight + specular bileşenlerle gerçekçi aydınlatma sağlar.
- Fener açık değilken ambient düşüktür, fener açıldığında ışık efektleri etkinleşir.

---

## 🔁 Kullanıcı Etkileşimi

| Tuşlar       | İşlev                                       |
|--------------|----------------------------------------------|
| `E`          | Feneri yak                                   |
| `1 / 2`      | Yol seç (Patika / Orman)                     |
| `WASD + Fare`| Serbest kamera modunda gezinti               |
| `C`          | Kamera modları arasında geçiş yap            |
| `ESC`        | Uygulamadan çıkış                            |

---

##  :sparkles: Ekran Görüntüleri

![image](https://github.com/user-attachments/assets/a1d18b4e-686c-47af-8fe9-6f5cb323a415)
![image](https://github.com/user-attachments/assets/7940c188-0999-4e05-a9c4-a1b6349a6569)
![image](https://github.com/user-attachments/assets/aafd7081-b6b1-46b2-a31e-337963b70c68)



