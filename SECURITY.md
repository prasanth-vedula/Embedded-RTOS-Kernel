# Security Policy

## Supported Versions

The following table describes the support status of released versions.

| Version | Supported |
|---------|-----------|
| 1.x.x | ✅ Yes |
| < 1.0 | ❌ No |

---

# Reporting a Vulnerability

If you discover a security issue, please do **not** create a public GitHub issue.

Instead:

- Describe the vulnerability clearly.
- Include steps to reproduce the issue.
- Explain the potential impact.
- Suggest a mitigation if possible.

The issue will be investigated and addressed in future releases.

---

# Scope

Security considerations include:

- Memory safety
- Buffer overflows
- Invalid pointer access
- Race conditions
- Synchronization issues
- Undefined behavior
- Resource leaks

---

# Security Goals

The Embedded RTOS aims to:

- Minimize undefined behavior
- Validate public API inputs
- Prevent resource leaks
- Promote safe synchronization primitives
- Encourage defensive programming practices

---

# Responsible Disclosure

Please allow reasonable time for investigation and remediation before publicly disclosing any security-related issue.

Thank you for helping improve the reliability and safety of this project.