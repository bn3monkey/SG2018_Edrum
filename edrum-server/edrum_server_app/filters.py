import rest_framework_filters as filters
from edrum_server_app.models import NoteFileModel, User

class NoteFileFilter(filters.FilterSet):
    class Meta:
        model = NoteFileModel
        fields = ['title', 'file', 'uploaded_at']

class UserFilter(filters.FilterSet):
    class Meta:
        model = User
        fields = ['user_id']