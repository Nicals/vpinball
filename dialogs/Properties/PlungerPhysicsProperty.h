#ifndef H_PLUNGER_PHYSICS_PROPERTY
#define H_PLUNGER_PHYSICS_PROPERTY

class PlungerPhysicsProperty: public BasePropertyDialog
{
public:
    PlungerPhysicsProperty(VectorProtected<ISelect> *pvsel);
    virtual ~PlungerPhysicsProperty()
    {
    }

    void UpdateVisuals(const int dispid=-1);
    void UpdateProperties(const int dispid);

protected:
    virtual BOOL OnInitDialog();

private:
    EditBox m_pullSpeedEdit;
    EditBox m_releaseSpeedEdit;
    EditBox m_strokeLengthEdit;
    EditBox m_scatterVelocityEdit;
    EditBox m_mechStrengthEdit;
    EditBox m_momentumXferEdit;
    EditBox m_parkPositionEdit;
    HWND    m_hEnableMechPlungerCheck;
    HWND    m_hAutoPlungerCheck;
};

#endif // !H_PLUNGER_PHYSICS_PROPERTY