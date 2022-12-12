#ifndef INC_2022_2_YOUNG_DEVS_GAMEWIDGET_H_
#define INC_2022_2_YOUNG_DEVS_GAMEWIDGET_H_

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

#include "../GameField/GameField.h"
//class PlayersPanel;

class GameWidget: public Wt::WContainerWidget {
 public:
    GameWidget(size_t rows = 3, size_t columns = 3);

 private:
    Wt::WText *title_;

    //PlayersPanel *panel_;

    Wt::WText *statusText_;

    GameField *field_;

    void registerCell();
};


#endif //INC_2022_2_YOUNG_DEVS_GAMEWIDGET_H_
