#include "object/Points.h"

extern int MapaZPliku[25][50];
extern wxSize defaultSize;
extern unsigned int pixelSizeBit;
/// Array of Points, Buffs and DeBuffs
Punkt TablicaPunktow[Punkt::MAX_PUNKTOW];

bool Punkt::Collide(int x,int y) { // Check If Point Collides With Dot Or No
    return (::MapaZPliku[y][x] == 32);
}

Punkt::Punkt(int px, int py, unsigned int w, wxPanel * panel){ // Constructor Declaration
        this->x = px; this->y = py; this->Wartosc = w;
        this->Image = new wxStaticBitmap(panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, defaultSize, 0);
        this->Image->SetPosition( wxPoint( this->x << pixelSizeBit, this->y << pixelSizeBit) );

        this->change_znak( this->Wartosc, Punkt::Collide( this->x, this->y ) == true );
}

void Punkt::change_znak(int val,bool isEmpty){ // Function To Change Point Image
        switch (val) {
        // Slow Image
        case Punkt::SLOW_BUFF:
            if (isEmpty == true)   this->Image->SetBitmap(wxBitmap("PacmanImages\\Slow.bmp",  wxBITMAP_TYPE_BMP)); // Debuff Image
            else                   this->Image->SetBitmap(wxBitmap("PacmanImages\\Slow2.bmp", wxBITMAP_TYPE_BMP)); // Debuff Image
        break;
        // Speed Image
        case Punkt::SPEED_BUFF:
            if (isEmpty == true)   this->Image->SetBitmap(wxBitmap("PacmanImages\\Speed.bmp",  wxBITMAP_TYPE_BMP)); // Buff Image
            else                   this->Image->SetBitmap(wxBitmap("PacmanImages\\Speed2.bmp", wxBITMAP_TYPE_BMP)); // Buff Image
        break;
        // Coint Image
        default:
            if (isEmpty == true)   this->Image->SetBitmap(wxBitmap("PacmanImages\\Point.bmp",  wxBITMAP_TYPE_BMP)); // Point Image
            else                   this->Image->SetBitmap(wxBitmap("PacmanImages\\Point2.bmp", wxBITMAP_TYPE_BMP)); // Point Image
        }

}

///TODO better looking functions (More Readable)
void Punkt::GeneratorPunktow(wxPanel * panel, unsigned int punkty){ // Create Point In Random Positions
    for (unsigned int i = 0; i < punkty; i++){
        ::TablicaPunktow[i] = Punkt::Nastepny_Punkt( panel ); // Generare new Points
    }
}

Punkt Punkt::Nastepny_Punkt(wxPanel * panel){ // Create Next Point In Random Positions
    while (true){
        int punktX = rand() % MAP_X, punktY = rand() % MAP_Y; // Generate New Position
        if (::MapaZPliku[punktY][punktX] == 32 || ::MapaZPliku[punktY][punktX] == (int)'.'){ // Until Position is not A Wall

            int pointType = (rand() % Punkt::MAX_BUFF_VALUE + 1);
            if ((rand() & 0b10) && pointType == Punkt::SLOW_BUFF) // Smaller Chanse To Be Slow
                pointType = (rand() % Punkt::MAX_BUFF_VALUE + 1);

            return Punkt ( punktX, punktY, pointType, panel );
        }
    }
}

void Punkt::WypiszPunkty( void ){ // Override All Points => Refresh()
    for (unsigned int i = 0; i < Punkt::MAX_PUNKTOW; i++){
        ::TablicaPunktow[i].Image->Refresh();
    }
}
