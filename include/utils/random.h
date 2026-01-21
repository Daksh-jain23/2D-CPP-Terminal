class Random {
public:
    static void Init();   // call once
    static int GetRandomInt(int x, int y);       // [x, y]
    static float GetRandomFloat(float x, float y); // [x, y)
};
