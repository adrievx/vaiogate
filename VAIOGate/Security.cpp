#include "Security.h"
#include <Aclapi.h>
#include <sddl.h>
#include <tchar.h>

bool GrantFileAccess(LPWSTR filePath, LPCWSTR sidString) {
	bool success = false;
	PSID pSid = nullptr;
	PSECURITY_DESCRIPTOR pSD = nullptr;
	PACL pOldDacl = nullptr;
	PACL pNewDacl = nullptr;

	if (ConvertStringSidToSidW(sidString, &pSid)) {
		DWORD dwRes = GetNamedSecurityInfoW(filePath, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, &pOldDacl, nullptr, &pSD);

		if (dwRes == ERROR_SUCCESS) {
			EXPLICIT_ACCESSW ea = {};
			ea.grfAccessPermissions = GENERIC_ALL;
			ea.grfAccessMode = GRANT_ACCESS;
			ea.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
			ea.Trustee.pMultipleTrustee = nullptr;
			ea.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
			ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
			ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
			ea.Trustee.ptstrName = (LPWSTR)pSid;

			dwRes = SetEntriesInAclW(1, &ea, pOldDacl, &pNewDacl);
			if (dwRes == ERROR_SUCCESS) {
				dwRes = SetNamedSecurityInfoW(filePath, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, pNewDacl, nullptr);

				if (dwRes == ERROR_SUCCESS) {
					success = true;
				}
			}
		}
	}

	if (pNewDacl) {
		LocalFree(pNewDacl);
	}

	if (pSD) {
		LocalFree(pSD);
	}

	if (pSid) {
		LocalFree(pSid);
	}

	return success;
}
