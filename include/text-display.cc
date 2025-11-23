export module TextDisplay;

import Display;

export class TextDisplay : public Display {
public:
    void notify() override;
};