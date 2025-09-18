#pragma once
#include <atlbase.h>
#include <atlstr.h>
#include <atltime.h>
#include <ATLComTime.h>

COleDateTime* ParseIsoDate(COleDateTime* outDate, const CStringW& input);