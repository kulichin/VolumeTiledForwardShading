#pragma once


namespace Graphics
{
    class AdapterDXGI;

    class DisplayDXGI
    {
    public:
        DisplayDXGI( Microsoft::WRL::ComPtr<IDXGIOutput4> output );
        ~DisplayDXGI();

        /**
        * A name that describes the display device.
        */
        const std::wstring& GetName() const;

        /**
        * Get the desktop coordinates of this display device.
        */
        const Rect& GetDesktopCoordinates() const;

        /**
        * Get the display rotation.
        */
        DisplayRotation GetRotation() const;

        /**
        * Get the display modes supported by this display.
        */
        DisplayModeList GetDisplayModes( const TextureFormat& textureFormat ) const;

        /**
         * Get a pointer to the underlying DXGIOutput.
         */
        Microsoft::WRL::ComPtr<IDXGIOutput4> GetDXGIOutput() const;
    protected:

    private:
        Microsoft::WRL::ComPtr<IDXGIOutput4> m_dxgiOutput;
        DXGI_OUTPUT_DESC  m_dxgiOutputDescription;
        std::wstring m_DisplayName;
        Rect m_DesktopCoordinates;
        DisplayRotation m_Rotation;
    };
}