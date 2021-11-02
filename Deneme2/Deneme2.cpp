// Deneme2.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.

#include <iostream>
#include "PhyObject.h"
#include <vector>
#include "engine.h"
#include "baseShape.h"

int main()
{
    double posx1 = 0, posy1 = 0, velx1 = 0, vely1 = 0, rad1 = 0, mass1 = 1, angle = 0, angularVel = 0;
    int i=2;
    baseShape* shape = nullptr;
    enum PhyObject::ObjectState state = PhyObject::ObjectState::NotFixed;

    engine* addObject = new engine();
    
    for (; i > 0; --i) {
        PhyObject* object = new PhyObject(posx1, posy1, velx1, vely1, mass1, angle, angularVel, shape, state);
        addObject->add(object);
    }

    const std::vector<const PhyObject*> objList= addObject->GetPhyObjects();
    
    std::cout << objList[0]->GetPositionX();
    delete addObject;
    //addObject->run();
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
