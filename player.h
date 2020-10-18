namespace InkEngine
{
    class player
    {
        public:
            int xpos = 0;
            int ypos = 0;
            float Vvelocity = 0;
            float Hvelocity = 0;
            int mass = 70;
            void update();
            
    };
}