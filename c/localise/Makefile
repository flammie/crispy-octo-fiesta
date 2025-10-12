# quite minimal makefile for gettext-based translation in C
# a normal usage would be to use autotools and call gettextize

prefix=local
LINGUAS=fi en nb sv se hu fr de
PACKAGENAME=crispy-octo-fiesta

.PHONY: update-po gmo install clean

all: localise gmo $(PACKAGENAME).pot

localise: localise.c gettext.h
	$(CC) $(CFLAGS) -DENABLE_NLS localise.c -o localise

gettext.h: /usr/share/gettext/gettext.h
	cp -v $< $@

$(PACKAGENAME).pot: localise.c
	xgettext --language=C --output=$@ \
		--package-name=$(PACKAGENAME) \
		--package-version=0.0.0 \
		--msgid-bugs-address="Flammie <flammie@iki.fi>" $<

%.po: $(PACKAGENAME).pot
	if test -f $@ ; then \
		msgmerge --update $@ $<; \
	else \
		msginit -i $< -o $@ -l $* ; \
	fi

%.gmo: %.po
	msgfmt -cv --output-file=$@ $<

clean:
	-rm -f *.po $(PACKAGENAME).pot localise gettext.h

update-po: $(PACKAGENAME).pot
	for l in $(LINGUAS) ; do \
		$(MAKE) $$l.po ; \
	done

gmo:
	for l in $(LINGUAS) ; do \
		$(MAKE) $$l.gmo ; \
	done

install:
	for l in $(LINGUAS); do \
		install -d $(prefix)/share/locale/$$l/LC_MESSAGES ; \
		install -c -m 644 $$l.gmo \
			$(prefix)/share/locale/$$l/LC_MESSAGES/$(PACKAGENAME).mo ; \
	done
	install -d $(prefix)/bin
	install -c localise $(prefix)/bin/
