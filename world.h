namespace InkEngine
{
    class world
    {
        public:
            float gravity = -9.81;
            float floorFriction = -0.2;
            void update();
    };
}