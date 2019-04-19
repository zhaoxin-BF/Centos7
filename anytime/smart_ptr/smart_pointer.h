
template<typename T>
class smart_pointer
{
    private:
        T* m_pRawPointer;
    public:
        smart_pointer(T* pData): m_pRawPointer(pData){}

        //复制构造函数
        smart_pointer(const smart_pointer & anotherSP);

        //赋值 = 
        smart_pointer& operator=(const smart_pointer& anotherSP);

        //*号 *
        T& operator* () const
        {
            return *(m_pRawPointer);
        }

        //
        T* operator-> () const
        {
            return m_pRawPointer;
        }
};
