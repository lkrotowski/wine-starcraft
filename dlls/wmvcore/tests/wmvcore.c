/*
 * Copyright 2017 Alistair Leslie-Hughes
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#include "initguid.h"
#include "wmsdkidl.h"

#include "wine/test.h"

static void test_wmwriter_interfaces(void)
{
    HRESULT hr;
    IWMWriter          *writer;
    IWMHeaderInfo      *header;
    IWMHeaderInfo2     *header2;
    IWMHeaderInfo3     *header3;

    hr = WMCreateWriter( NULL, &writer );
    ok(hr == S_OK, "WMCreateWriter failed 0x%08x\n", hr);
    if(FAILED(hr))
    {
        win_skip("Failed to create IWMWriter\n");
        return;
    }

    hr = IWMWriter_QueryInterface(writer, &IID_IWMHeaderInfo, (void **)&header);
    todo_wine ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMWriter_QueryInterface(writer, &IID_IWMHeaderInfo2, (void **)&header2);
    todo_wine ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMWriter_QueryInterface(writer, &IID_IWMHeaderInfo3, (void **)&header3);
    todo_wine ok(hr == S_OK, "Failed 0x%08x\n", hr);

    if(header)
        IWMHeaderInfo_Release(header);
    if(header2)
        IWMHeaderInfo2_Release(header2);
    if(header3)
        IWMHeaderInfo3_Release(header3);
    IWMWriter_Release(writer);
}

static void test_wmreader_interfaces(void)
{
    HRESULT hr;
    IWMReader          *reader;
    IWMReaderAdvanced  *advanced;
    IWMReaderAdvanced2 *advanced2;
    IWMHeaderInfo      *header;
    IWMHeaderInfo2     *header2;
    IWMHeaderInfo3     *header3;
    IWMProfile         *profile;

    hr = WMCreateReader( NULL, 0, &reader );
    ok(hr == S_OK, "WMCreateReader failed 0x%08x\n", hr);
    if(FAILED(hr))
    {
        win_skip("Failed to create IWMReader\n");
        return;
    }

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderAdvanced, (void **)&advanced);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMReaderAdvanced2, (void **)&advanced2);
    ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMHeaderInfo, (void **)&header);
    todo_wine ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMHeaderInfo2, (void **)&header2);
    todo_wine ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMHeaderInfo3, (void **)&header3);
    todo_wine ok(hr == S_OK, "Failed 0x%08x\n", hr);

    hr = IWMReader_QueryInterface(reader, &IID_IWMProfile, (void **)&profile);
    todo_wine ok(hr == S_OK, "Failed 0x%08x\n", hr);

    if(advanced)
        IWMReaderAdvanced_Release(advanced);
    if(advanced2)
        IWMReaderAdvanced2_Release(advanced2);
    if(profile)
        IWMProfile_Release(profile);
    if(header)
        IWMHeaderInfo_Release(header);
    if(header2)
        IWMHeaderInfo2_Release(header2);
    if(header3)
        IWMHeaderInfo3_Release(header3);

    IWMReader_Release(reader);
}

void test_profile_manager_interfaces(void)
{
    HRESULT hr;
    IWMProfileManager  *profile;

    hr = WMCreateProfileManager(&profile);
    ok(hr == S_OK, "WMCreateProfileManager failed 0x%08x\n", hr);
    if(FAILED(hr))
    {
        win_skip("Failed to create IWMProfileManager\n");
        return;
    }

    IWMProfileManager_Release(profile);
}

START_TEST(wmvcore)
{
    HRESULT hr;

    hr = CoInitialize(0);
    ok(hr == S_OK, "failed to init com\n");
    if(hr != S_OK)
        return;

    test_wmreader_interfaces();
    test_wmwriter_interfaces();
    test_profile_manager_interfaces();

    CoUninitialize();
}
