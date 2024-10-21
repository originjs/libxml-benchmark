SUBDIRS= tools xmlgen parse create validate xsl security

.PHONY: all install clean
all install clean:
	@target=`echo $@ | sed s/-recursive//`; \
	list='$(SUBDIRS)'; \
	for subdir in $$list; do \
	    echo "Making $$target in $$subdir"; \
	    $(MAKE) -C $$subdir $$target || \
	    exit 1 ; \
	done
