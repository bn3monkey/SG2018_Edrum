#import rest_framework_filters as filters
#import django_filters
from django_filters import rest_framework as filters
from edrum_server_app.models import NoteFileModel, User

class NoteFileFilter(filters.FilterSet):
    class Meta:
        model = NoteFileModel
        fields = ['server_id', 'name', 'artist', 'ID', 'date']

class UserFilter(filters.FilterSet):
    class Meta:
        model = User
        fields = ['user_id']