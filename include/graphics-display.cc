export module GraphicsDisplay;

import Display;

export class GraphicsDisplay : public Display {
public:
    void notify() override;
};