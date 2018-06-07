import rest_framework_filters as filters
from edrum_server_app.models import NoteFileModel

class NoteFileFilter(filters.FilterSet):
    class Meta:
        model = NoteFileModel
        fields = ['title', 'file', 'uploaded_at']