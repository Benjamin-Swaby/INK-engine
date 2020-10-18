namespace InkEngine
{
    class player
    {
        public:
            float xpos = 0;
            float ypos = 0;
            float Vvelocity = 0;
            float Hvelocity = 0;
            int mass = 30;
            void update();
            
    };
}