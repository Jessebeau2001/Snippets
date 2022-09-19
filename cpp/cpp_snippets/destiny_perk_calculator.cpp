#include <iostream>

using std::cout;

enum PerkA { TRIPLE_TAP = 3, FOURTH_TIME = 4 };
enum PerkB { FOCUSED_FURY, VORPAL, FIREING_LINE };

int main()
{
    PerkA s_perkA = TRIPLE_TAP;
    PerkB s_perkB = FOCUSED_FURY;
    int mag_size = 7;
    
    int b_used = 0;
    int b_stash = 0;
    int b_left = mag_size;
    
    double dmg_mod = 0.0;
    double dmg_total_extra = 0.0;
    
    switch(s_perkB) {
        case VORPAL: dmg_mod = 0.1; break;
        case FIREING_LINE: dmg_mod = 0.2; break;
    }
    
    while (b_left > 0) {
        b_left--;
        b_used++;
        b_stash++;
        dmg_total_extra += dmg_mod;
        
        if (s_perkB == FOCUSED_FURY && ((double) b_used / mag_size) > .5 && dmg_mod != 0.2) {
            cout << "Focused-fury procced!\n";
            dmg_mod = 0.2;
        }
        
        cout << "shot nr: " << b_used << ", bullets_left: " << b_left << "\n";
        
        if (b_stash >= s_perkA) {
            b_stash = 0;
            b_left += (s_perkA == 3 ? 1 : 2);
            cout << (s_perkA == 3 ? "Triple-tap" : "Fourth-time") << " procced!\n";
        }
    }
    
    cout << "Total amount of bullets shot: " << b_used << ", total extra dmg from perk: " << dmg_total_extra * 100 << "%";

    return 0;
}
