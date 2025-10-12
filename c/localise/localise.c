#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <libintl.h>
#if HAVE_GETTEXT_H
#include <gettext.h>
#endif

int main(int argc, char** argv) {
    char* rv = setlocale(LC_ALL, "");
    if (rv == NULL) {
        fprintf(stderr, "Cannot setlocale()\n");
        return EXIT_FAILURE;
    }
    rv = bindtextdomain("crispy-octo-fiesta", "local/share/locale/");
    if (rv == NULL) {
        fprintf(stderr, "Cannot bindtextdomain()\n");
        return EXIT_FAILURE;
    }
    rv = textdomain("crispy-octo-fiesta");
    if (rv == NULL) {
        fprintf(stderr, "Cannot bindtextdomain()\n");
        return EXIT_FAILURE;
    }
    printf(gettext("Hello world!\n"));
    for (unsigned int i = 0; i < 21; i++) {
        printf(ngettext("There is now %d wug.\n", "There are now %d wugs.\n",
                        i), i);
    }
    for (int i = 1; i < argc; ++i) {
        printf(gettext("Unrecognised command line argument %s\n"), argv[i]);
    }
    /* the following example is a bit contrived but shows a real problem with
     * gettext: some small string need different translations in context.
     * This happens commonly in GUI: button label 'read' not the same as status
     * bar label 'read' (in most other languages). Below the word 'read' is
     * used 3 ways which would require different translations for many
     * languages. This can be fixed in gettext but requires
     * localisation-friendly developers.
     */
    printf(gettext("Do you want to %s a file?"), gettext("read"));
    printf(gettext("\n - "));
    printf(gettext("read"));
    printf(gettext("\n - "));
    printf(gettext("do not read"));
    printf("\n");
    printf(gettext("Reading... "));
    printf(gettext("read"));
    printf("\n");
    /* this is a better version, for docu see:
     * https://www.gnu.org/software/gettext/manual/html_node/Contexts.html
     */
#if HAVE_PGETTEXT
    printf(gettext("Do you want to %s a file?"), pgettext("do you want to",
                                                          "read"));
    printf(gettext("\n - "));
    printf(pgettext("I want to", "read"));
    printf(gettext("\n - "));
    printf(gettext("do not read"));
    printf("\n");
    printf(gettext("Reading... "));
    printf(pgettext("file has been", "read"));
    printf("\n");
    printf(gettext("This is some hidden gettext infos:\n"));
    printf(gettext(""));
#endif
    return EXIT_SUCCESS;
}
