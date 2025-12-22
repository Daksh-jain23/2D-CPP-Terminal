    double lastTime = static_cast<double>(GetTickCount64());
    while(true){
        double currentTime = static_cast<double>(GetTickCount64());
        double dt = (currentTime - lastTime) / 1000.0;
        lastTime = currentTime;
        player.Control();

        Transform playerTransform = player.transform;
        player.update(dt);
        Draw::drawByValue(
            Draw::MergeValues(
                Draw::getValueMap(
                    [](double x, double y) {
                        return Functions::Circle::value(x, y, 0.5);
                    },
                    playerTransform
                ),
                Draw::getValueMap(
                    [](double x, double y) {
                        return Functions::Square::value(x, y, 0.4);
                    },
                    Transform{{1, 1}}
                ),
                Draw::getValueMap(
                    [](double x, double y) {
                        return Functions::Square::value(x, y ,0.4);
                    },
                    Transform{{-1, 0.5}}
                )
            )
        );
       