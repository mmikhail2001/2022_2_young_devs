#include "GameField.h"

#include <iostream>

GameField::GameField(size_t rows, size_t columns): Wt::WCompositeWidget(),
    playerOrder_(true) {



    field_ = new Wt::WTable();

    setImplementation(std::unique_ptr<Wt::WTable>(field_));

    field_->resize(rows, columns);

    size_t numberOfCells = rows * columns;
    for (size_t i = 0; i < numberOfCells; i++) {
        std::string c(1, '\0');
        Wt::WPushButton *cell = field_->elementAt(i / columns, i % columns)->addWidget(
                std::make_unique<Wt::WPushButton>(c)
                );

        cellButtons_.push_back(cell);
        cell->resize(Wt::WLength(30), Wt::WLength(30));

        cell->clicked().connect(std::bind(&GameField::processButton, this, cell));

        T_GameField *field 	= new ST_Field;
        T_GameLogic *logic 	= new ST_Logic;
        T_Output 	*output = new T_WtOutput(cellButtons_);
        T_Bot       *bot 	= new ST_Bot;
        player_1 	= { .id = 0, .isBot = false,  .cell = TypeCell::X };
        player_2 	= { .isBot = true,  .cell = TypeCell::O };
        // GameRoom *room 		= new T_Room(player_1, player_2, field, logic, output, bot);
        room 		        = new T_Room(player_1, player_2, field, logic, output, bot, TypeGame::ST);


        //connections_.push_back(Wt::WApplication::instance()->globalKeyPressed().connect(
        //        std::bind(&GameField::processButtonPushed, this, std::placeholders::_1, cell)
        //        ));
    }
}

GameField::~GameField() {
    for (auto &connection: connections_) {
        connection.disconnect();
    }
}

void GameField::processButton(Wt::WPushButton *button) {
    /*
    button->disable();
    if (playerOrder_) {
        button->setText("X");
    } else {
        button->setText("O");
    }
     */
    auto convertToBlocks = [](size_t index){
        size_t i = index / 9;
        size_t j = index % 9;
        size_t start_index_in_block = ((i / 3) * 3 + (j / 3)) * 9;
        return start_index_in_block + (i % 3) * 3 + (j % 3);
    };

    size_t numberOfCell = 0;
    for (size_t i = 0; i < cellButtons_.size(); i++) {
        if (cellButtons_[i] == button) {

            //cellPressed_.emit(numberOfCell++);
            numberOfCell = i;


        }
    }

    std::cout << "НАШ ХОД" << convertToBlocks(numberOfCell) << std::endl;

    T_StepTask task(room, player_1, convertToBlocks(numberOfCell));
    task();

    //if (playerOrder_) {

    //} else {
    //    T_StepTask task(room, player_2, numberOfCell);
    //    task();
    //}

    //playerOrder_ = not playerOrder_;

}

//void GameField::processButtonPushed(const Wt::WKeyEvent &e,
//                                    Wt::WPushButton *button) {
//    if (Wt::WCompositeWidget::isHidden())
//        return;

    //if(e.key() == static_cast<Wt::Key>(button->text().toUTF8()[0]))
    //    processButton(button);
//}